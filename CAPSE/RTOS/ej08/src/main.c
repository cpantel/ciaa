/*
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and defInitions]=================================*/

typedef enum { DOWN,RISING,UP,FALLING} STATES;

#define TASK1INTERVAL 50
#define TASK2INTERVAL 200


/*==================[internal data declaration]==============================*/


uint32_t task1Count = 0;
uint32_t task2Count = 0;

uint32_t task3Data = 0;

bool_t task1Enabled = true;
bool_t task2Enabled = true;

static char uartBuffer[20];

/*==================[internal functions declaration]=========================*/

void task1Writer();
void task2AntiBounceRead();
void task3Uart();

/*==================[internal data defInition]===============================*/

/*==================[external data defInition]===============================*/

/*==================[internal functions defInition]==========================*/

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}



void task1Init() {
   gpioConfig(TEC1, GPIO_INPUT); 
}

void task2Init() {
   gpioConfig(LED1, GPIO_OUTPUT); 
}


void task3Init() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready v3\n");
}

void task1DebouncedRead() {
   static STATES state = UP;
   static int32_t counter = 0;
   static uint32_t interval = 0;
   if (state == DOWN) {
      counter += 100;
   }

   ++interval; 

   if (interval >= TASK1INTERVAL) {
      return;
   }

   interval = 0;   

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
            task3Data = counter;
            counter = 0;
            task3Uart();
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
         } else {
            state = UP;
         }
         break;
      }
   }      
}

void task2Writer() {
   gpioToggle(LED1);
}


void task3Uart() {
   itoa( (int) (task3Data), (char*)uartBuffer, 10 );
   uartWriteString( UART_USB, uartBuffer );
   uartWriteByte( UART_USB, 10);
}

/*==================[external functions defInition]==========================*/

static bool_t scheduler(void *ptr) {
   ++task1Count;
   ++task2Count;
   

   task1Enabled = false;
   task2Enabled = false;

   if (task1Count == TASK1INTERVAL ) {
     task1Count = 0;
     task1Enabled = true;
   }

   if (task2Count == TASK2INTERVAL ) {
     task2Count = 0;
     task2Enabled = true;
   }

   return 0;
}

void dispatcher() {
   if (task1Enabled) {
      task1DebouncedRead();
   }
   if (task2Enabled) {
      task2Writer();
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
