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
   gpioConfig(TEC2, GPIO_INPUT);
   gpioConfig(TEC3, GPIO_INPUT);
   gpioConfig(TEC4, GPIO_INPUT);
   gpioConfig(LED1, GPIO_OUTPUT);


   bool_t led = false;
   int delayTime = 250;
   
   while(1) {
      gpioWrite( LED1, led );
      led = ! led;

      if (! gpioRead(TEC1) || ! gpioRead(TEC2) || ! gpioRead(TEC3) || ! gpioRead(TEC4) ) {
        if (! gpioRead(TEC1)) {
          delayTime = 150;
        }

        if (! gpioRead(TEC2)) {
          delayTime = 250;
        }
         if (! gpioRead(TEC3)) {
          delayTime = 500;
        }
          if (! gpioRead(TEC4)) {
          delayTime = 1000;
        }
     }
      delay(delayTime);
   }

   return 0 ;
}

/*==================[end of file]============================================*/
