/*
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

#define TICK_AMPLITUDE 500

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

uint8_t task1run = false;
uint8_t task2run = false;
uint8_t task3run = false;

uint8_t task1period = 4;
uint8_t task2period = 2;
uint8_t task3period = 1;


uint32_t task1counter = 0;
uint32_t task2counter = 0;
uint32_t task3counter = 0;

uint8_t led1 = false;
uint8_t led2 = false;
uint8_t led3 = false;


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void task1init() {
   gpioConfig(LED1, GPIO_OUTPUT);
}


void task2init() {
  gpioConfig(LED2, GPIO_OUTPUT);
}

void task3init() {
   gpioConfig(LED3, GPIO_OUTPUT);

}

void task1() {
  led1 = !led1;
  gpioWrite(LED1, led1);

}

void task2() {
  led2 = !led2;
  gpioWrite(LED2, led2);
}


void task3() {
  led3 = !led3;
  gpioWrite(LED3, led3);
}



void scheduler() {
   ++task1counter;
   if (task1counter == task1period) {
      task1run = true;
      task1counter = 0;
   } else {
      task1run = false;
   }
   ++task2counter;
   if (task2counter == task2period) {
      task2run = true;
      task2counter = 0;
   } else {
      task2run = false;
   }
   ++task3counter;
   if (task3counter == task3period) {
      task3run = true;
      task3counter = 0;
   } else {
      task3run = false;
  }

}

void dispatcher() {
   if (task1run) {
      task1();
   }
   if (task2run) {
      task2();
   }
   if (task3run) {
      task3();
   }
}

/*==================[external functions definition]==========================*/


int main(void){
   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();
   
   task1init();
   task2init();
   task3init();

   delay_t delay;

   delayConfig(&delay, TICK_AMPLITUDE);

   while(1) {

    if (delayRead(&delay)) {
      scheduler();
      dispatcher();
    }


   }

   return 0 ;
}

/*==================[end of file]============================================*/
