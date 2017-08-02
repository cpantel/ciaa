/*
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

#define TICK_AMPLITUDE 1000

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

void task1init();
void task2init();
void task3init();

void task1run();
void task2run();
void task3run();

/*==================[internal data definition]===============================*/

struct task_t {
  uint8_t enabled;
  uint8_t period;
  uint8_t led;
  uint32_t counter;
  void (*init)(void);
  void (*run)(void);
};

struct task_t task[3] = {
  {false, 1, false, 0, &task1init, &task1run},
  {false, 2, false, 0, &task2init, &task2run},
  {false, 3, false, 0, &task3init, &task3run}
};


uint32_t tickCount = 0;

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

void task1run() {
  task[0].led = !task[0].led;
  gpioWrite(LED1, task[0].led);

}

void task2run() {
  task[1].led = !task[1].led;
  gpioWrite(LED2, task[1].led);
}


void task3run() {
  task[2].led = !task[2].led;
  gpioWrite(LED3, task[2].led);
}


void scheduler() {
   uint8_t idx;
   for (idx = 0; idx < 3 ; ++idx) {
      ++task[idx].counter;
      if (task[idx].counter == task[idx].period ) {
         task[idx].enabled = true;
         task[idx].counter == 0;
      } else {
         task[idx].enabled = false;
      }     
   }
}

void dispatcher() {
   uint8_t idx;
   for (idx = 0; idx < 3 ; ++idx) {
      if (task[idx].enabled) {
         task[idx].run();
      }
   }
}

/*==================[external functions definition]==========================*/


int main(void){
   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();
   uint8_t idx;
   for (idx=0; idx< 3; ++idx) { 
     task[idx].run();
   }   

   delay_t delay;

   delayConfig(&delay, TICK_AMPLITUDE);

   while(1) {

    if (delayRead(&delay)) {
      scheduler();
      dispatcher();
      ++tickCount;      
    }


   }

   return 0 ;
}

/*==================[end of file]============================================*/
