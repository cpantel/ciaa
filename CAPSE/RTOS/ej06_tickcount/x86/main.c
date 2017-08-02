/*
 */
#include <stdio.h>
/*==================[inclusions]=============================================*/


/*==================[macros and definitions]=================================*/

#define TICK_AMPLITUDE 500

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

int task1run = 0;
int task2run = 0;
int task3run = 0;

int task1period = 4;
int task2period = 2;
int task3period = 1;

int led1 = 0;
int led2 = 0;
int led3 = 0;


int tickCount = 0;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

void task1() {
  led1 = !led1;

}

void task2() {
  led2 = !led2;
}


void task3() {
  led3 = !led3;
}



void scheduler() {
   task1run = ( ( tickCount % task1period ) == 0 );
   task2run = ( ( tickCount % task2period ) == 0 );
   task3run = ( ( tickCount % task3period ) == 0 );
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

   int t = 0;
   for(t=0; t< 20; ++t) {

    scheduler();
    dispatcher();
    printf("%d :  %d   %d   %d \n", tickCount, led1, led2, led3);

    ++tickCount;      


   }

   return 0 ;
}

/*==================[end of file]============================================*/
