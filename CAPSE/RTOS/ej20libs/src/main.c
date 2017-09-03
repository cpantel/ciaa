/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/
#include "stdio.h"
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "common.h"

/*==================[definiciones y macros]==================================*/

typedef enum { DOWN,RISING,UP,FALLING} STATES;  // FSM debouncer

uint32_t debouncerCounter = 0;

typedef enum { WAITING_1, WAITING_2} DELTA_STATES;

typedef struct {
  STATES state;
  uint8_t tec;
  uint32_t evt;
  uint32_t task;
} TECS;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

void MonitorInit() {
   gpioConfig(LED1, GPIO_OUTPUT);
}


void TecInit() {
  gpioConfig(TEC1, GPIO_INPUT);
  gpioConfig(TEC2, GPIO_INPUT);
}


void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej20libs build 6\n");
}

TASK (Alive) {
   gpioToggle(LEDR);
   TerminateTask();
}

TASK (DeltaTime) {
   DELTA_STATES state = WAITING_1;

   uint32_t counter;

   EventMaskType events;

   while (1) {
      WaitEvent( EvtTec1  | EvtTec2   );

      GetEvent(DeltaTime, &events);
      bool_t t1 =  false;
      bool_t t2 =  false;

      if ( events & EvtTec1) {
         ClearEvent(EvtTec1);
         t1 = true;
      }
 
      if ( events & EvtTec2) {
         ClearEvent(EvtTec2);
         t2 = true;
      }

      switch (state) {
         case WAITING_1:
            if (t1) {
               counter = debouncerCounter;
               state=WAITING_2;
            } else {

            }
         break;

         case WAITING_2:
            if (t2) {
               // will fail in day 25 * 40 because of the sign
               // will fail in day 50 * 50 because of the overflow
               int elapsed = (debouncerCounter - counter ) * 40 ; // TODO: replace with proper call
               char buffer[32];
               itoa(elapsed, buffer, 10);
               uartWriteString( UART_USB, "Elapsed time: ");
               uartWriteString( UART_USB, buffer);
               uartWriteString( UART_USB, " ms\n");
               state = WAITING_1;
            } else {
               counter = debouncerCounter;
            }
         break;
         default: 

         break;

      }

   }

}

TASK (ReadTec) {
   static TECS tec[2] = {
      {UP,TEC1,EvtTec1,DeltaTime},
      {UP,TEC2,EvtTec2,DeltaTime}
   };
 
   // TODO: protect
   ++debouncerCounter;

   uint8_t idx;
   for (idx = 0; idx < 2; ++idx) {

      int pressed = ! gpioRead(tec[idx].tec);
      switch ( tec[idx].state ) {
         case DOWN: {
            if (pressed) {
               // keep DOWN
            } else {
               tec[idx].state = RISING;
            }
            break;
         }
         case RISING: {
            if (pressed) {
               // revert
               tec[idx].state = DOWN;
            } else {
               // change
               tec[idx].state = UP;
//               if (callbackUP()) callbackUP(idx);
            }
            break;
         }
         case UP: {
            if (pressed) {
               tec[idx].state = FALLING;
            } else {
               // keep UP
            }
            break;
         }
         case FALLING: {
            if (pressed ) {
               // change
               tec[idx].state = DOWN;
               SetEvent(tec[idx].task, tec[idx].evt);

//               if (callbackDOWN()) callbackDOWN(idx);
            } else {
               // revert
               tec[idx].state = UP;
            }
            break;
         }
      }
   }
   TerminateTask();
}

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

int main( void )
{
   StartOS(AppMode1);
   return 0;
}

void StartupHook(void) {
   boardConfig();   
   UartMonitorInit();
   TecInit();
   MonitorInit();
} 

void ErrorHook(void)
{
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
