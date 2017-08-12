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

void ReadTec1Init() {
   gpioConfig(TEC1, GPIO_INPUT); 
}

void BlinkLed1Init() {
   gpioConfig(LED3, GPIO_OUTPUT); 
}

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   StartOS(AppMode1);
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

TASK(BlinkLed3) {
   gpioToogle(LED3);
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
            counter = 0;
            // ActivateTask(ShowElapsedTime);
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

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
