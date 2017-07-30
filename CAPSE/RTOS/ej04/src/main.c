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
   STATES state = UP;

   boardConfig();


   gpioConfig(TEC1, GPIO_INPUT);


   gpioConfig(LED1, GPIO_OUTPUT);

   delay_t delay;

   delayConfig(&delay, 50);

   uint32_t counter = 0;
   uint8_t go = false; 
  
   while(1) {

    if (delayRead(&delay)) {
      if (go) {
         if (counter > 0) { 
            gpioWrite( LED1, ON );
            --counter;
         } else {
            gpioWrite( LED1, OFF);
            go = false;
         }
      }
      


      int pressed = ! gpioRead(TEC1);
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
             state = UP;
           }
           break;
         }
         case UP: {
           if (pressed) {
             state = FALLING;
           } else {
             go = true;
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


   }

   return 0 ;
}

/*==================[end of file]============================================*/
