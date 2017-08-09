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
uint32_t tickCount = 0;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}
void ReadTec1Init() {
   gpioConfig(TEC1, GPIO_INPUT); 
}

void BlinkLed1Init() {
   gpioConfig(LED1, GPIO_OUTPUT); 
}


void ShowElapsedTimeInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek v3\n");
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
   ReadTec1Init();
   BlinkLed1Init();
   ShowElapsedTimeInit();
} 

void ErrorHook(void)
{
	ShutdownOS(0);
}

TASK(BlinkLed1) {
   gpioToggle(LED1);
   TerminateTask();

}

TASK(ReadTec1)
{
   static STATES state = UP;
   static int32_t counter = 0;

   int pressed = ! gpioRead(TEC1);
   switch ( state ) {
      case DOWN: {
         if (pressed) {
            counter+=50;
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
            tickCount = counter;
            counter = 0;
            ActivateTask(ShowElapsedTime);
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
         } else {
            state = UP;
         }
         break;
      }
   }      
   TerminateTask();
}
TASK(ShowElapsedTime) {
   char uartBuffer[20];
   itoa( (int) (tickCount), (char*)uartBuffer, 10 );
   uartWriteString( UART_USB, uartBuffer );
   uartWriteByte( UART_USB, 10);
   TerminateTask();

}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
