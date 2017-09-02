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


/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/



void LedInit() {
   gpioConfig(LEDR, GPIO_OUTPUT);
   gpioConfig(LED1, GPIO_OUTPUT);
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioConfig(LED3, GPIO_OUTPUT);
}

void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej19libs build 1\n");
}

TASK (BlinkLed1) {
   gpioToggle(LED1);
   WaitEvent(TurnOffLed1Evt);
   gpioToggle(LED1);
   ClearEvent(TurnOffLed1Evt);
   TerminateTask();
}
TASK (BlinkLed2) {
   gpioToggle(LED2);
   WaitEvent(TurnOffLed2Evt);
   gpioToggle(LED2);
   ClearEvent(TurnOffLed2Evt);
   TerminateTask();
}
TASK (BlinkLed3) {
   gpioToggle(LED3);
   WaitEvent(TurnOffLed3Evt);
   gpioToggle(LED3);
   ClearEvent(TurnOffLed3Evt);
   TerminateTask();
}
TASK (BlinkLedR) {
   gpioToggle(LEDR);
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
   LedInit();
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
