/*
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

   typedef enum { DOWN,RISING,UP,FALLING} STATES;

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();

   gpioConfig(TEC2, GPIO_INPUT);
   gpioConfig(TEC3, GPIO_INPUT);
   gpioConfig(TEC4, GPIO_INPUT);

   gpioConfig(LED1, GPIO_OUTPUT);
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioConfig(LED3, GPIO_OUTPUT);

   delay_t delay;

   delayConfig(&delay, 50);

   struct readerTask_t {
     uint32_t counter;
     uint8_t tec;
     STATES state;
 

   };

   struct writerTask_t {
     uint32_t counter;
     uint8_t led;
   };


   struct readerTask_t readers[3] = {
       {0, TEC2, UP}, 
       {0, TEC3, UP}, 
       {0, TEC4, UP} 
   };

   struct writerTask_t writers[3] = {
       {0, LED1}, 
       {0, LED2}, 
       {0, LED3} 
   };


   while(1) {
    uint8_t idx;
    if (delayRead(&delay)) {
      for (idx = 0; idx < 3; ++idx) {
         if (writers[idx].counter > 0) { 
            gpioWrite( writers[idx].led, ON );
            --(writers[idx].counter);
         } else {
            gpioWrite( writers[idx].led, OFF);
         }
      

      int pressed = ! gpioRead(readers[idx].tec);
      switch ( readers[idx].state ) {
         case DOWN: {
           if (pressed) {
             ++readers[idx].counter;
           } else {
             readers[idx].state = RISING;
           }
           break;
         }
         case RISING: {
           if (pressed) {
             readers[idx].state = DOWN;
           } else {
             writers[idx].counter = readers[idx].counter;
             readers[idx].counter = 0;
             readers[idx].state = UP;
           }
           break;
         }
         case UP: {
           if (pressed) {
             readers[idx].state = FALLING;
           } else {
          }
           break;
         }
         case FALLING: {
           if (pressed) {
             readers[idx].state = DOWN;
             readers[idx].counter++;
           } else {
             readers[idx].state = UP;
           }
           break;
         }
      }
    }      
    }

   }

   return 0 ;
}

/*==================[end of file]============================================*/
