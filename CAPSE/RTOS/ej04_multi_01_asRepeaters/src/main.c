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

   struct repeater_t {
     uint32_t counter;
     uint8_t go; 
     uint8_t led;
     uint8_t tec;
     STATES state;
   };

   struct repeater_t repeaters[3] = {
       {0,false, LED1, TEC2, UP}, 
       {0,false, LED2, TEC3, UP}, 
       {0,false, LED3, TEC4, UP} 
   };

   while(1) {
     uint8_t idx;
     if (delayRead(&delay)) {
      for (idx = 0; idx < 3; ++idx) {
      if (repeaters[idx].go) {
         if (repeaters[idx].counter > 0) { 
            gpioWrite( repeaters[idx].led, ON );
            --(repeaters[idx].counter);
         } else {
            gpioWrite( repeaters[idx].led, OFF);
            repeaters[idx].go = false;
         }
      }
      

      int pressed = ! gpioRead(repeaters[idx].tec);
      switch ( repeaters[idx].state ) {
         case DOWN: {
           if (pressed) {
             ++repeaters[idx].counter;
           } else {
             repeaters[idx].state = RISING;
           }
           break;
         }
         case RISING: {
           if (pressed) {
             repeaters[idx].state = DOWN;
           } else {
             repeaters[idx].state = UP;
           }
           break;
         }
         case UP: {
           if (pressed) {
             repeaters[idx].state = FALLING;
           } else {
             repeaters[idx].go = true;
           }
           break;
         }
         case FALLING: {
           if (pressed) {
             repeaters[idx].state = DOWN;
             repeaters[idx].counter++;
           } else {
             repeaters[idx].state = UP;
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
