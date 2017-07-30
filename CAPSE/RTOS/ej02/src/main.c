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


int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();


   gpioConfig(TEC1, GPIO_INPUT);
   gpioConfig(TEC3, GPIO_INPUT);
   gpioConfig(LED1, GPIO_OUTPUT);


   bool_t led = false;
   int delayTime = 250;
  
   delay_t delay;
   delayConfig( &delay, delayTime );
 
   while(1) {
      if (delayRead(&delay)) {
         gpioWrite( LED1, led );
         led = ! led;
         delayWrite(&delay,delayTime);
      }

      if (! gpioRead(TEC1)) {
         delayTime = 500;
      }

      if (! gpioRead(TEC3)) {
         delayTime = 1000;
      }
   }

   return 0 ;
}

/*==================[end of file]============================================*/
