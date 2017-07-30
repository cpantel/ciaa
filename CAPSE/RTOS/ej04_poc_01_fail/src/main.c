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


   gpioConfig(LED1, GPIO_OUTPUT);
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioConfig(LED3, GPIO_OUTPUT);
   gpioConfig(LEDG, GPIO_OUTPUT);

   int counter = 0;
  
   while(1) {

      if (! gpioRead(TEC1)) {
        counter++; 
      }
      
      gpioWrite( LEDG, counter & 1 );
      gpioWrite( LED1, counter & 2 );
      gpioWrite( LED2, counter & 4 );
      gpioWrite( LED3, counter & 8 );


   }

   return 0 ;
}

/*==================[end of file]============================================*/
