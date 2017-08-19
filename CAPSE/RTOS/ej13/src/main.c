/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

/*==================[definiciones y macros]==================================*/
typedef enum { DOWN,RISING,UP,FALLING} STATES;

typedef struct {
  STATES state;
  uint8_t tec;
  uint32_t evt;
} TASKS;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
void ReadEvtTecInit() {
   gpioConfig(TEC1, GPIO_INPUT);
   gpioConfig(TEC2, GPIO_INPUT);
   gpioConfig(TEC3, GPIO_INPUT);
   gpioConfig(TEC4, GPIO_INPUT);
}

void BlinkLed1Init() {
   gpioConfig(LED1, GPIO_OUTPUT);
}

void DisplayInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "\nReady osek ej13\n");
}

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

int main( void )
{
   StartOS(AppMode1);
   return 0;
}

void StartupHook(void) {
   boardConfig();   
   ReadEvtTecInit();
   BlinkLed1Init();
   DisplayInit();
} 

void ErrorHook(void)
{
   uartWriteString(UART_USB, "\nShutdownOS\n");
   ShutdownOS(0);
}

TASK(Display) {

   EventMaskType events;

   while (1) {
      WaitEvent( Asterisk  | EvtTec1  | EvtTec2  | EvtTec3 | EvtTec4 );

      GetEvent(Display, &events);

      if ( events & Asterisk ) {
         uartWriteByte( UART_USB, 42 );
         ClearEvent(Asterisk);
      }
      if ( events & EvtTec1) {
         uartWriteString( UART_USB, "\nEvtTec1\n"  );
         ClearEvent(EvtTec1);
      }

      if ( events & EvtTec2) {
         uartWriteString( UART_USB, "\nEvtTec2\n"  );
         ClearEvent(EvtTec2);
      }
 
      if ( events & EvtTec3) {
         uartWriteString( UART_USB, "\nEvtTec3\n"  );
         ClearEvent(EvtTec3);
      }
 
      if ( events & EvtTec4) {
         uartWriteString( UART_USB, "\nEvtTec4\n"  );
         ClearEvent(EvtTec4);
      }
 
   }
   TerminateTask();

}

TASK(BlinkLed1) {
   gpioToggle(LED1);
   TerminateTask();

}

TASK(ReadTec)
{

   static TASKS task[4] = {
      {UP,TEC1,EvtTec1},
      {UP,TEC2,EvtTec2},
      {UP,TEC3,EvtTec3},
      {UP,TEC4,EvtTec4}
   };

   uint8_t idx;
   for (idx = 0; idx < 4; ++idx) {

      int pressed = ! gpioRead(task[idx].tec);
      switch ( task[idx].state ) {
         case DOWN: {
            if (pressed) {
            } else {
               task[idx].state = RISING;
            }
            break;
         }
         case RISING: {
            if (pressed) {
               task[idx].state = DOWN;
            } else {
               task[idx].state = UP;
            }
            break;
         }
         case UP: {
            if (pressed) {
               task[idx].state = FALLING;
            } else {
            }
            break;
         }
         case FALLING: {
            if (pressed ) {
               task[idx].state = DOWN;
               SetEvent(Display, task[idx].evt);
            } else {
               task[idx].state = UP;
            }
            break;
         }
      }
   }
   TerminateTask();
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
