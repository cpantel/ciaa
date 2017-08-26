/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

/*==================[definiciones y macros]==================================*/


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
   uartWriteString( UART_USB, "ready osek ej14\n");
}

TASK (BlinkLed1) {
   static uint8_t count = 0;
   if (count ==4 ) {
     CancelAlarm(ActivateBlinkLed1);
   }
   count++;
 
   gpioToggle(LED1);
   ActivateTask(BlinkLed2);
   TerminateTask();
}

TASK (BlinkLed2) {
   gpioToggle(LED2);
   TerminateTask();
} 

TASK (BlinkLed3) {
   gpioToggle(LED3);
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
