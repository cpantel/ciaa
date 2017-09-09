/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "common.h"

/*==================[definiciones y macros]==================================*/

typedef enum { DOWN,RISING,UP,FALLING} DEBOUNCER_STATES;  // FSM debouncer

uint32_t debouncerCounter = 0;

typedef enum { START, READ_COMMAND, READ_ARGUMENTS } PACKET_STATES; // FSM packets

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

void MonitorInit() {
   gpioConfig(LED1, GPIO_OUTPUT);
}


void ResetInit() {
  gpioConfig(TEC1, GPIO_INPUT);
}

void ShowInit() {
  gpioConfig(LEDR, GPIO_OUTPUT);
  gpioConfig(LEDB, GPIO_OUTPUT);

}

void UartInit() {
   uartConfig( UART_USB, 19200 );
   uartWriteString( UART_USB, "ready osek examen_v1 build 11\n");
}


TASK (ShowGoodPacket) {
   static bool_t firstCall = true;
   gpioToggle(LEDB);
   if (firstCall) {
      firstCall = false;
   } else {
      firstCall = true;
      CancelAlarm(ActivateShowGoodPacket);
   }
   TerminateTask();
}

TASK (ShowBadPacket) {
   static bool_t firstCall = true;
   gpioToggle(LEDR);
   if (firstCall) {
      firstCall = false;
   } else {
      firstCall = true;
      CancelAlarm(ActivateShowBadPacket);
   }
   TerminateTask();
}
TASK (Alive) {
   gpioToggle(LED1);
   TerminateTask();
}

TASK (ReadReset) {
//   GetResource(CountLock);
//   ++debouncerCounter;
//   ReleaseResource(CountLock);

   static  DEBOUNCER_STATES state = UP;


   int pressed = ! gpioRead(TEC1);
   switch ( state ) {
      case DOWN: {
         if (pressed) {
            // keep DOWN
         } else {
            state = RISING;
         }
         break;
      }
      case RISING: {
         if (pressed) {
            // revert
            state = DOWN;
         } else {
            // change
            state = UP;
            // if (callbackUP()) callbackUP(idx);
         }
         break;
      }
      case UP: {
         if (pressed) {
            state = FALLING;
         } else {
            // keep UP
         }
         break;
      }
      case FALLING: {
         if (pressed ) {
            // change
            state = DOWN;
            SetEvent(Statistics, EvtReset);
            // if (callbackDOWN()) callbackDOWN(idx);
         } else {
            // revert
            state = UP;
         }
         break;
      }
   }
   TerminateTask();
}

TASK (ReadPacket) {
   static PACKET_STATES state = START;
   static uint8_t command;
   uint8_t charRead; 
   if ( uartReadByte(UART_USB, &charRead) ) {
      switch (state) {
         case START:
            if (charRead == '<') {
               state = READ_COMMAND;
            } else {
               SetEvent(Statistics,EvtError);
            }
         break;

         case READ_COMMAND:
            if (charRead == '<' ){
               SetEvent(Statistics,EvtError);
            } else if (charRead == 'Q' || charRead == 'S' || charRead == 'R' || charRead == 'E') {
               command = charRead;
               state = READ_ARGUMENTS;
            } else {
               state = START;
               SetEvent(Statistics,EvtError);
            }
         break;

         case READ_ARGUMENTS:
            if (charRead == '>') {
               state = START;
               switch (command) {
                  case 'Q': SetEvent(Statistics, EvtQok); break;
                  case 'S': SetEvent(Statistics, EvtSok); break;
                  case 'R': SetEvent(Statistics, EvtRok); break;
                  case 'E': SetEvent(Statistics, EvtEok); break;
                  default : /*unhandled error*/ ; break;
               }
            } else if (charRead == '<') {
               state = START;
               SetEvent(Statistics,EvtError);
            } else if (charRead >= 32 && charRead <= 127) {
               // printable ascii
            } else {
               state = START;
               SetEvent(Statistics,EvtError); 
            }
         break;
         default:
            /* unhandled error */
         break;

      }
   }

   TerminateTask();
}

TASK (Statistics) {
   uint32_t qOk = 0;
   uint32_t sOk = 0;
   uint32_t rOk = 0;
   uint32_t eOk = 0;
   uint32_t error = 0;

   EventMaskType events;
   while (1) {
      WaitEvent( EvtReset | EvtShow | EvtError | EvtQok | EvtSok | EvtRok | EvtEok );
      GetEvent(Statistics, &events);

      if ( events & EvtReset) {
         ClearEvent(EvtReset);
         qOk = 0;
         sOk = 0;
         rOk = 0;
         eOk = 0;
         error = 0;
      }
 
      if ( events & EvtShow) {
         ClearEvent(EvtShow);
         char buffer[32];
         itoa(qOk, buffer, 10);
         uartWriteString( UART_USB, "Q: ");
         uartWriteString( UART_USB, buffer);

         itoa(sOk, buffer, 10);
         uartWriteString( UART_USB, " S: ");
         uartWriteString( UART_USB, buffer);

         itoa(rOk, buffer, 10);
         uartWriteString( UART_USB, " R: ");
         uartWriteString( UART_USB, buffer);
         itoa(eOk, buffer, 10);
         uartWriteString( UART_USB, " E: ");
         uartWriteString( UART_USB, buffer);
         itoa(error, buffer, 10);
         uartWriteString( UART_USB, " error: ");
         uartWriteString( UART_USB, buffer);
         uartWriteString( UART_USB, "\n");
      }

      if ( events & EvtError) {
         ClearEvent(EvtError);
         SetRelAlarm(ActivateShowBadPacket,0,50);
         ++error;
      }

      if ( events & EvtQok) {
         ClearEvent(EvtQok);
         SetRelAlarm(ActivateShowGoodPacket,0,50);
         ++qOk;
      }

      if ( events & EvtSok) {
         ClearEvent(EvtSok);
         SetRelAlarm(ActivateShowGoodPacket,0,50);
         ++sOk;
      }

      if ( events & EvtRok) {
         ClearEvent(EvtRok);
         SetRelAlarm(ActivateShowGoodPacket,0,50);
         ++rOk;
      }

      if ( events & EvtEok) {
         ClearEvent(EvtEok);
         SetRelAlarm(ActivateShowGoodPacket,0,50);
         ++eOk;
      }
   }
}



/*
TASK (DeltaTime) {
   DELTA_STATES state = WAITING_1;

   uint32_t counter;
   uint32_t debouncerCounterCopy;

   EventMaskType events;

   while (1) {
      WaitEvent( EvtTec1  | EvtTec2   );

      GetEvent(DeltaTime, &events);
      bool_t t1 =  false;
      bool_t t2 =  false;

      if ( events & EvtTec1) {
         ClearEvent(EvtTec1);
         t1 = true;
      }
 
      if ( events & EvtTec2) {
         ClearEvent(EvtTec2);
         t2 = true;
      }

      if (t1 || t2) {
         GetResource(CountLock);
         debouncerCounterCopy = debouncerCounter;
         ReleaseResource(CountLock);
      }


      switch (state) {
         case WAITING_1:
            if (t1) {
               counter = debouncerCounterCopy;
               state=WAITING_2;
            } else {

            }
         break;

         case WAITING_2:
            if (t2) {
               // will fail in day 25 * 40 because of the sign
               // will fail in day 50 * 50 because of the overflow
               int elapsed = (debouncerCounterCopy - counter ) * 40 ; // TODO: replace with proper call
               char buffer[32];
               itoa(elapsed, buffer, 10);
               uartWriteString( UART_USB, "Elapsed time: ");
               uartWriteString( UART_USB, buffer);
               uartWriteString( UART_USB, " ms\n");
               state = WAITING_1;
            } else {
               counter = debouncerCounterCopy;
            }
         break;
         default: 

         break;

      }

   }

}
*/




/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

int main( void )
{
   StartOS(AppMode1);
   return 0;
}

void StartupHook(void) {
   boardConfig();   

   MonitorInit();
   ResetInit();
   ShowInit();
   UartInit();
} 

void ErrorHook(void)
{
   printError();
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
