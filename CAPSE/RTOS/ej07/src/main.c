/*
 */

/*==================[inclusions]=============================================*/

#include "seos.h"         /* <= own header */

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

typedef enum { DOWN,RISING,UP,FALLING} STATES;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

void taskLed1();
void taskLed2();
void taskAntiBounceRead();

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

void taskLed1() {
   gpioToggle(LED1);
}

void taskLed2() {
   gpioToggle(LED2);
}

void taskAntiBounceRead() {
   static STATES state = UP;
   static uint8_t = 0;

   int pressed = ! gpioRead(readers[idx].tec);
   switch ( state ) {
      case DOWN: {
         if (pressed) {
            ++counter;
         } else {
            state = RISING;
         }
         break;
      }
      case RISING: {
         if (pressed) {
            state = DOWN;
         } else {
            writers[idx].counter = readers[idx].counter;
            counter = 0;
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
         if (pressed) {
            state = DOWN;
            counter++;
         } else {
            state = UP;
         }
         break;
      }
   }      
}

static bool_t myTickHook(void *ptr){

   scheduleAndDispatchTasks();
   return 0;
}


/*==================[external functions definition]==========================*/


int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();

   gpioConfig(TEC1, GPIO_INPUT);

   gpioConfig(LED1, GPIO_OUTPUT);
   gpioConfig(LED2, GPIO_OUTPUT);


   tickConfig( 1, myTickHook );
   while (1) {
      
      sleepUntilNextInterrupt();

   }
   return 0 ;
}

/*==================[end of file]============================================*/
