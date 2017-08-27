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


# define BUFFER_SIZE   CIRCULAR_BUFFER_SET_SIZE(32) 

uint8_t bufferMemory[ BUFFER_SIZE ];
circularBuffer_t buffer;
uint8_t currentCounter;

void LedInit() {
   gpioConfig(LEDR, GPIO_OUTPUT);
   gpioConfig(LED1, GPIO_OUTPUT);
}

void BufferInit() {
   circularBuffer_Config(&buffer, bufferMemory, BUFFER_SIZE, 4); // 4 is the size of a pointer to a byte
}

void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej18 build 13\n");
}

TASK (BlinkLed1) {
   GetResource(CountLock);
   
   if (currentCounter == 0 ) {
      CancelAlarm(ActivateBlinkLed1);
   } else {
      gpioToggle(LED1);
      --currentCounter;
   }
   ReleaseResource(CountLock);
 
   TerminateTask();
}

TASK (BlinkLedR) {
   gpioToggle(LEDR);
   TerminateTask();
}

TASK (ReadUart) {
   uint8_t count; 
   if ( uartReadByte(UART_USB, &count) ) {
      if (count >= '0' && count <= '9') {
         count = (count - '0' ) * 2;
         circularBufferWrite(&buffer,&count);
      }
   }
   
   GetResource(CountLock);
   if (currentCounter == 0) {
      
      circularBufferRead(&buffer,&currentCounter);
      if (currentCounter != 0) {
         SetRelAlarm(ActivateBlinkLed1,1000,250);
      }
   }
   ReleaseResource(CountLock);
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
   BufferInit();
   LedInit();
} 

void ErrorHook(void)
{
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
