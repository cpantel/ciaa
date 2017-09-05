/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "common.h"

/*==================[definiciones y macros]==================================*/

typedef enum { DOWN,RISING,UP,FALLING} STATES;  // FSM debouncer

uint32_t elapsedTime      = 0;
uint32_t elapsedTimeAccum = 0;
uint32_t hits             = 0;

typedef enum { WAITING_DOWN, WAITING_UP} DELTA_STATES;

typedef struct {
  STATES state;
  uint8_t tec;
  uint32_t evtUp;
  uint32_t evtDown;
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
   uartWriteString( UART_USB, "ready osek ej21libs build 17\n");
}

TASK (Alive) {
   gpioToggle(LEDR);
   TerminateTask();
}

TASK (DeltaTime) {
   DELTA_STATES state = WAITING_DOWN;

   EventMaskType events;

   while (1) {
      
      WaitEvent( EvtTecUP  | EvtTecDOWN   );

      GetEvent(DeltaTime, &events);
      bool_t up        = false;
      bool_t down      = false;
      bool_t updateAvg = false;
      bool_t start     = false;
      bool_t stop      = false;

      if ( events & EvtTecUP) {
         ClearEvent(EvtTecUP);
         up = true;
      }
 
      if ( events & EvtTecDOWN) {
         ClearEvent(EvtTecDOWN);
         down = true;
      }
     

      switch (state) {
         case WAITING_DOWN:
            if (down) {
               start = true;
               state=WAITING_UP;
            } else {

            }
         break;

         case WAITING_UP:
            if (up) {
               state = WAITING_DOWN;
               stop = true;
            } else {

            }
         break;
         default: 

         break;

      }
     
      if (start || stop ) {
         GetResource(CountLock);
         if (stop) {
         // will fail in day 25 / 40 because of the sign
         // will fail in day 50 / 50 because of the overflow
            elapsedTimeAccum += elapsedTime * 40 ; // TODO: replace with proper call
         }
         elapsedTime = 0;
         ReleaseResource(CountLock);

      }
   }
}

TASK (ShowAvg) {
   char buffer[32];
   float localAvg;
   uint32_t   localHits;
   uint32_t   localElapsedTimeAccum;

   GetResource(CountLock);
   localHits = hits;
   localElapsedTimeAccum = elapsedTimeAccum;
   ReleaseResource(CountLock);

   itoa(localHits,buffer,10);
   uartWriteString( UART_USB, "Hits: ");
   uartWriteString( UART_USB, buffer);

   itoa(localElapsedTimeAccum, buffer,10);
   uartWriteString( UART_USB, " elapsed: ");
   uartWriteString( UART_USB, buffer);
 

   float avg = ( localElapsedTimeAccum / hits);
   ftoa(avg, buffer, 4);
   uartWriteString( UART_USB, " Avg: ");
   uartWriteString( UART_USB, buffer);
   uartWriteString( UART_USB, " pushes by \n");
   TerminateTask();
}

TASK (ReadTec) {
   static TECS tec[1] = {
      {UP,TEC1,EvtTecUP,EvtTecDOWN,DeltaTime},
   };
 
   GetResource(CountLock);
   ++elapsedTime;
   ++hits;
   ReleaseResource(CountLock);

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
               SetEvent(tec[idx].task, tec[idx].evtUp);
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
               SetEvent(tec[idx].task, tec[idx].evtDown);

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
   printError();
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
