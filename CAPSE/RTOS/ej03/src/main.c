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
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioConfig(LED3, GPIO_OUTPUT);

  
   bool_t led1 = false;
   bool_t led2 = false;
   bool_t led3 = false;

   int delayTime1 = 250;
   int delayTime2 = 250;
   int delayTime3 = 250;

   delay_t delay1;
   delay_t delay2;
   delay_t delay3;

 
   delayConfig( &delay1, delayTime1 );
   delayConfig( &delay2, delayTime2 );
   delayConfig( &delay3, delayTime3 );

   while(1) {
      if (delayRead(&delay1)) {
         gpioWrite( LED1, led1 );
         led1 = ! led1;
         delayWrite(&delay1,delayTime1);
      }
      if (delayRead(&delay2)) {
         gpioWrite( LED2, led2 );
         led2 = ! led2;
         delayWrite(&delay2,delayTime2);
      }
      if (delayRead(&delay3)) {
         gpioWrite( LED3, led3 );
         led3 = ! led3;
         delayWrite(&delay3,delayTime3);
      }

      if (! gpioRead(TEC1)) {
         delayTime1 = 250;
         delayTime2 = 250;
         delayTime3 = 250;
      }
      if (! gpioRead(TEC2)) {
         delayTime1 = 250;
         delayTime2 = 500;
         delayTime3 = 750;
      }
      if (! gpioRead(TEC3)) {
         delayTime1 = 750;
         delayTime2 = 500;
         delayTime3 = 250;
      }
      if (! gpioRead(TEC4)) {
         delayTime1 = 1000;
         delayTime2 = 1000;
         delayTime3 = 1000;
      }




   }

   return 0 ;
}

/*==================[end of file]============================================*/
