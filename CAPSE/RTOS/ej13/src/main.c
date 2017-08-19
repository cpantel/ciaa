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

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
void ReadTecInit() {
   gpioConfig(TEC1, GPIO_INPUT);
   gpioConfig(TEC2, GPIO_INPUT);
   gpioConfig(TEC3, GPIO_INPUT);
   gpioConfig(TEC4, GPIO_INPUT);
}

void BlinkLed1Init() {
   gpioConfig(LED1, GPIO_OUTPUT);
}

void DisplayInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "\nReady osek ej13\n");
}

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
  
   StartOS(AppMode1);
   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

void StartupHook(void) {
   boardConfig();   
   ReadTecInit();
   BlinkLed1Init();
   DisplayInit();
} 

void ErrorHook(void)
{
   uartWriteString(UART_USB, "\nShutdownOS\n");
   ShutdownOS(0);
}

TASK(Display) {
   while (1) {
     WaitEvent(Asterisk);
     

     uartWriteByte( UART_USB, 42 );

     ClearEvent(Asterisk);

   }
   TerminateTask();

}

TASK(BlinkLed1) {
   gpioToggle(LED1);
   TerminateTask();

}

TASK(ReadTec)
{
   static STATES state = UP;

   int pressed = ! gpioRead(TEC1);
   switch ( state ) {
      case DOWN: {
         if (pressed) {
         } else {
            state = RISING;
         }
         break;
      }
      case RISING: {
         if (pressed) {
            state = DOWN;
         } else {
            state = UP;
         }
         break;
      }
      case UP: {
         if (pressed) {
            state = FALLING;

         } else {
         }
         break;
      }
      case FALLING: {
         if (pressed ) {
            state = DOWN;
            SetEvent(Display, Tec1);
         } else {
            state = UP;
         }
         break;
      }
   }
   TerminateTask();
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
