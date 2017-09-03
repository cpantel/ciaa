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

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

void printError(void) 
{
   static uint8_t OSErrorGetServiceIdTxt[][25]={
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

   static uint8_t OSErrorGetRetTxt[][13]={
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
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
