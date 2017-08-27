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

void Tec1Init() {
   // taken from freertos example
   Chip_SCU_GPIOIntPinSel(0,0,4);
   Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);
   Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH0);


//   gpioConfig(TEC1, GPIO_INPUT);
  
}

ISR (ISRtec) {
   gpioWrite(LED2,1);
}

TASK (BlinkLed1) {
   gpioToggle(LED1);
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
