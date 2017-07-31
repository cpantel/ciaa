/*
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

#define DELAY_INCREMENT 200

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


int main(void){
   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();

   uartConfig( UART_USB, 115200 );

   delay_t delay;

   delayConfig(&delay, 1);

   gpioConfig(LED1, GPIO_OUTPUT);  //POC

   uint32_t next = 0;
   uint32_t myTime = 0;
   uint8_t led = false; // POC  

   uartWriteString(UART_USB, "init\n");

   while(1) {

    if (delayRead(&delay)) {
      if (myTime == next) {
        uartWriteString(UART_USB, "msg\n");

        gpioWrite(LED1, led); // POC
        led = ! led;          // POC
        next += DELAY_INCREMENT;
        myTime = 0;
      } else {
        ++myTime;
      }
    }      


   }

   return 0 ;
}

/*==================[end of file]============================================*/
