/*
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and defInitions]=================================*/

typedef enum { DOWN,RISING,UP,FALLING} STATES;

#define TASK1INTERVAL 1000
#define TASK2INTERVAL 1300
#define TASK3INTERVAL 50


/*==================[internal data declaration]==============================*/

bool_t tasksPaused = false;


uint32_t task1Count = 0;
uint32_t task2Count = 0;
uint32_t task3Count = 0;


bool_t task1Enabled = true;
bool_t task2Enabled = true;
bool_t task3Enabled = true;

/*==================[internal functions declaration]=========================*/

void task1Writer();
void task2Writer();
void taskAntiBounceRead();

/*==================[internal data defInition]===============================*/

/*==================[external data defInition]===============================*/

/*==================[internal functions defInition]==========================*/
void task1Init() {
   gpioConfig(LED1, GPIO_OUTPUT); 
}

void task2Init() {
   gpioConfig(LED2, GPIO_OUTPUT); 
}

void task3Init() {
   gpioConfig(TEC1, GPIO_INPUT); 
}

void task1Writer() {
   gpioToggle(LED1);
}

void task2Writer() {
   gpioToggle(LED2);
}

void task3DebouncedRead() {
   static STATES state = UP;

   int pressed = ! gpioRead(TEC1);
   switch ( state ) {
      case DOWN: {
         if (pressed) {
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
            tasksPaused = false;
         }
         break;
      }
      case UP: {
         if (pressed) {
            state = FALLING;
            
         } else {
         }
         break;
      }
      case FALLING: {
         if (pressed ) {
            state = DOWN;
            tasksPaused = true;
         } else {
            state = UP;
         }
         break;
      }
   }      
}

/*==================[external functions defInition]==========================*/

static bool_t scheduler(void *ptr) {
   if (!tasksPaused) {
      ++task1Count;
      ++task2Count;
   }
   ++task3Count;


   task1Enabled = false;
   task2Enabled = false;
   task3Enabled = false;

   if (task1Count == TASK1INTERVAL ) {
     task1Count = 0;
     task1Enabled = true;
   }

   if (task2Count == TASK2INTERVAL ) {
     task2Count = 0;
     task2Enabled = true;
   }


   if (task3Count == TASK3INTERVAL ) {
     task3Count = 0;
     task3Enabled = true;
   }

  return 0;
}

void dispatcher() {
   if (task1Enabled) {
      task1Writer();
   }
   if (task2Enabled) {
      task2Writer();
   }
   if (task3Enabled) {
      task3DebouncedRead();
   }
}

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   boardConfig();

   task1Init();
   task2Init();
   task3Init();

   tickConfig( 1, scheduler );
   while (1) {
      dispatcher();    
      sleepUntilNextInterrupt();

   }
   return 0 ;
}

/*==================[end of file]============================================*/
