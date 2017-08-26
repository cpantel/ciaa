/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

/*==================[definiciones y macros]==================================*/

typedef enum { DOWN,RISING,UP,FALLING} STATES;

typedef struct {
  STATES state;
  uint8_t tec;
  uint32_t evt;
  uint32_t task;
} TECS;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

void Led1Init() {
   gpioConfig(LED1, GPIO_OUTPUT);
}


void Led2Init() {
  gpioConfig(LED2, GPIO_OUTPUT);
}

void Led3Init() {
  gpioConfig(LED3, GPIO_OUTPUT);
}

void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej17 build 20\n");
}
TASK (ToggleLed1) {
   while (1) {
      WaitEvent(Tec1Pressed);
      ClearEvent(Tec1Pressed);
      gpioToggle(LED1);
   }
   TerminateTask();
}

TASK (ToggleLed2) {
   while (1) {
      WaitEvent(Tec2Pressed);
      ClearEvent(Tec2Pressed);
      gpioToggle(LED2);
   }
   TerminateTask();
}

TASK (ReadTec) {
   static TECS tec[2] = {
      {UP,TEC1,Tec1Pressed,ToggleLed1},
      {UP,TEC2,Tec2Pressed,ToggleLed2}
   };

   uint8_t idx;
   for (idx = 0; idx < 2; ++idx) {

      int pressed = ! gpioRead(tec[idx].tec);
      switch ( tec[idx].state ) {
         case DOWN: {
            if (pressed) {
            } else {
               tec[idx].state = RISING;
            }
            break;
         }
         case RISING: {
            if (pressed) {
               tec[idx].state = DOWN;
            } else {
               tec[idx].state = UP;
            }
            break;
         }
         case UP: {
            if (pressed) {
               tec[idx].state = FALLING;
            } else {
            }
            break;
         }
         case FALLING: {
            if (pressed ) {
               tec[idx].state = DOWN;
//               SetEvent(tec[idx].task, tec[idx].evt);

            } else {
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
   Led1Init();
   Led2Init();
} 

void ErrorHook(void)
{
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
