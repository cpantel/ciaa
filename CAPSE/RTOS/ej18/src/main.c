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


void Led1Init() {
   gpioConfig(LED1, GPIO_OUTPUT);
}

void Led3Init() {
  gpioConfig(LED3, GPIO_OUTPUT);
}

void BufferInit() {
   circularBuffer_Config(&buffer, bufferMemory, BUFFER_SIZE, 4);
}

void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej18 build 03\n");
}

TASK (BlinkLed1) {
   uint8_t count = 0;
   GetResource(BufferLock);
   
   circularBufferRead(&buffer,&count);
   
   ReleaseResource(BufferLock);
   count += 42;
 
   gpioToggle(LED1);
//   ActivateTask(BlinkLed2);
   TerminateTask();
}

TASK (BlinkLed3) {
   gpioToggle(LED3);
   TerminateTask();
}

TASK (ReadUart) {
   uint8_t count; 
   uartWriteString(UART_USB, "Reading...\n");
   if ( uartReadByte(UART_USB, count) ) {
      uartWriteString(UART_USB, "   something read\n");
      GetResource(BufferLock);
//      circularBufferWrite(&buffer,&count);
      ReleaseResource(BufferLock);
      uartWriteByte(UART_USB,count);
      uartWriteByte(UART_USB,10);
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
   BufferInit();
   Led1Init();
   Led3Init();
} 

void ErrorHook(void)
{
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
