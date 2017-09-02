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



void LedInit() {
   gpioConfig(LEDR, GPIO_OUTPUT);
   gpioConfig(LED1, GPIO_OUTPUT);
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioConfig(LED3, GPIO_OUTPUT);
}

void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej19 build 12\n");
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
   uint8_t OSErrorGetServiceIdTxt[][25]={
      "Undefined",
      "ActivateTask",
      "TerminateTask",
      "ChainTask",
      "Schedule",
      "GetTAskID",
      "GetTaskState",
      "DisableAllInterrupts",
      "EnableAllInterrupts",
      "SuspendAllInterrupts",
      "ResumeAllInterrupts",
      "SuspendOSInterrupts",
      "ResumeOSInterrupts",
      "GetResource",
      "ReleaseResource",
      "SetEvent",
      "ClearEvent",
      "GetEvent",
      "WaitEvent",
      "GetAlarmBase",
      "GetAlarm",
      "SetRelAlarm",
      "SetAbsAlarm",
      "CancelAlarm",
      "GetACtiveApplicationMode",
      "StartOS",
      "ShutdownOS"
   };

   uint8_t OSErrorGetRetTxt[][13]={
      "E_OK",
      "E_OS_ACCESS",
      "E_OS_CALLEVEL",
      "E_OS_ID"
      "E_OS_LIMIT",
      "E_OS_NOFUNC",
      "E_OS_RESOURCE",
      "E_OS_STATE",
      "E_OS_VALUE"
   };


   uartWriteString(UART_USB, "\n-----------------------------------\n");
   uartWriteString(UART_USB, "Service:\n");
   uartWriteByte(UART_USB, ( OSErrorGetServiceId() + 48 ) );

   uartWriteString(UART_USB, " = ");
   uartWriteString(UART_USB, ( OSErrorGetServiceIdTxt[OSErrorGetServiceId()]) );
   uartWriteString(UART_USB, " ---> ");
   uartWriteByte(UART_USB, ( OSErrorGetRet() + 48 ) );
   uartWriteString(UART_USB, " = ");
   uartWriteString(UART_USB, ( OSErrorGetRetTxt[OSErrorGetRet()] ) );

   uartWriteString(UART_USB, "\n-----------------------------------\n");
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
