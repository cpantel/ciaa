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
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioConfig(LED3, GPIO_OUTPUT);
   gpioConfig(LEDG, GPIO_OUTPUT);

   delay_t delay;

   delayConfig(&delay, 40);



   int counter = 0;
  
   while(1) {

    if (delayRead(&delay)) {

      int pressed = ! gpioRead(TEC1);
      switch ( state ) {
         case DOWN: {
           if (pressed) {
             state = DOWN;
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
             counter++;
           }
           break;
         }
         case UP: {
           if (pressed) {
             state = FALLING;
           } else {
             state = UP;
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
      gpioWrite( LEDG, counter & 1 );
      gpioWrite( LED1, counter & 2 );
      gpioWrite( LED2, counter & 4 );
      gpioWrite( LED3, counter & 8 );


   }

   return 0 ;
}

/*==================[end of file]============================================*/
