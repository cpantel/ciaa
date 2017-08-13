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

void BlinkLed3Init() {
   gpioConfig(LED3, GPIO_OUTPUT); 
}

void ShowElapsedTimeInit() {
   gpioConfig(LED1, GPIO_OUTPUT); 
}
/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

void StartupHook(void) {
   boardConfig();   
   ReadTec1Init();
   BlinkLed3Init();
   ShowElapsedTimeInit();
} 

void ErrorHook(void)
{
   ShutdownOS(0);
}

TASK(BlinkLed3) {
   gpioToggle(LED3);
   TerminateTask();
}

TASK(TickCounter) {
   ++tickCount; 
   TerminateTask();
}

TASK(ShowElapsedTime) {
   if (tickCount) {
      --tickCount;
   } else {
     CancelAlarm(ActivateShowElapsedTime);
//     SetRelAlarm(ActivateReadTec1,0,50);
   }

   TerminateTask();
}

TASK(ReadTec1)
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
            CancelAlarm(ActivateTickCounter);
//            CancelAlarm(ActivateReadTec1);
            SetRelAlarm(ActivateShowElapsedTime,0,50);
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
            SetRelAlarm(ActivateTickCounter, 0, 50);
         } else {
            state = UP;
         }
         break;
      }
   }      
   TerminateTask();
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   StartOS(AppMode1);
   return 0;
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
