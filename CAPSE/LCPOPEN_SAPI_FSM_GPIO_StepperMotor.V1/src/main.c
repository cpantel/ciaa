/** \brief Main example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/


/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */
#include "chip.h"
#include "sAPI.h"         /* <= sAPI header */

#include "fsm_stepperMotor.h"

#include "fsm_keyReader.h"

#include "util.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

uint8_t msgApagados[] = "Todos los Led apagados\r\n";

uint8_t msgMenu[][40] = {
      {"Seleccione el led a encender:\n"},
      {"\n"},
      {"r - Enciende el Led R.\n"},
      {"g - Enciende el Led G.\n"},
      {"b - Enciende el Led B.\n"},
      {"0 - Apaga todos los Leds.\n"},
      {"a - Apaga todos los Leds.\n"},
      {"    Menu\n"}
};

uint8_t msgKeyPressed[] =  "Tecla X presionada\n";

uint8_t msgLedOn[] = "Led X prendido\r\n";

uint8_t msgAnalogRead[] = "Lectura analogica xxxxx.\r\n";
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

void turnOffRGB() {
   digitalWrite( LEDR, 0 );
   digitalWrite( LEDG, 0 );
   digitalWrite( LEDB, 0 );
}

void turnOffnoRGB() {
   digitalWrite( LED1, 0 );
   digitalWrite( LED2, 0 );
   digitalWrite( LED3, 0 );
}

void updateLeds(int led1,int led2, int led3, int ledR, int ledG, int ledB) {
   digitalWrite( LEDR, ledR );
   digitalWrite( LEDG, ledG );
   digitalWrite( LEDB, ledB );
   digitalWrite( LED1, led1 );
   digitalWrite( LED2, led2 );
   digitalWrite( LED3, led3 );
}

void showMenu() {
   uint8_t idx;
   for(idx=0; idx < 10; idx++){
      uartWriteString(UART_USB,msgMenu[1]);
   }
   for(idx=0; idx < 7; idx++) {
      uartWriteString(UART_USB,msgMenu[idx]);
   }
}

void showPressedKey(int buttonName){

   msgKeyPressed[6] = '0' + buttonName;
   uartWriteString(UART_USB,msgKeyPressed);
}

void sayLedOn(char name) {
   msgLedOn[4] = name;
   uartWriteString(UART_USB, msgLedOn);
}

void turnOnLed(uint8_t led) {
   digitalWrite(led, 1);
}

void config(){
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar DigitalIO */
   digitalConfig( 0, INITIALIZE );

   analogConfig( ENABLE_ANALOG_INPUTS );

   /* Configuración de pines de salida para
      Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );

//   digitalConfig( DIO0, OUTPUT );
//   digitalConfig( DIO2, OUTPUT );
//   digitalConfig( DIO4, OUTPUT );
//   digitalConfig( DIO6, OUTPUT );

   uartConfig(UART_USB,9600);

   tickConfig(1);
}

uint8_t * updateAnalogReadMessage(int read) {
   uint8_t buffer[] = "123456789012345678901234567890123";
   itoa(read - 512 ,buffer,10);

   int idx;
   for( idx = 0; idx < 6 ; idx++) {
     if (buffer[idx] == 0 ) {
       msgAnalogRead[idx + 18] = ' ';
     } else {
         msgAnalogRead[idx + 18] = buffer[idx];
     }
   }
   return msgAnalogRead;
}

int main(void)
{
   uint8_t cmd;

    config();

    struct fsm_keyReader_t kr = createFsmKeyReader();
    struct fsm_StepperMotor_t sm = createFsmStepperMotor();

   showMenu();
   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      // digital input
        readKeys(&kr);
        if ( keyHasChanged(&kr, 1)) {
      ////     uartWriteString(UART_USB,"key 1 has changed\n\r");
        }

        if ( keyIsPressed(&kr, 1)) {
           showPressedKey(1);
        }
        if ( keyHasChanged(&kr, 2)) {
       ////    uartWriteString(UART_USB,"key 2 has changed\n\r");
        }

        if ( keyIsPressed(&kr, 2)) {
           showPressedKey(2);
        }
        if ( keyHasChanged(&kr, 3)) {
     ////      uartWriteString(UART_USB,"key 3 has changed\n\r");
        }

        if ( keyIsPressed(&kr, 3)) {
           showPressedKey(3);
        }
        if ( keyHasChanged(&kr, 4)) {
     ////      uartWriteString(UART_USB,"key 4 has changed\n\r");
        }

        if ( keyIsPressed(&kr, 4)) {
           showPressedKey(4);
        }

        // analog input
      int knob = analogRead(AI1) - 512;
        int absKnob = abs(knob);

        turnOffnoRGB();

        if (absKnob < 50) {
         turnOnLed(LED2);
         setSpeed(&sm,150);
         releaseStepperMotor(&sm);
      } else if (absKnob < 250) {
         turnOnLed(LED2);
         setSpeed(&sm,100);
         if (knob > 0) {
            turnOnLed(LED3);
            turnCCWStepperMotor(&sm);
         } else {
            turnOnLed(LED1);
            turnCWStepperMotor(&sm);
         }
      } else if (absKnob < 350) {
         setSpeed(&sm,25);
         if (knob > 0) {
            turnOnLed(LED3);
            turnCCWStepperMotor(&sm);
         } else {
            turnOnLed(LED1);
            turnCWStepperMotor(&sm);
         }
      } else if (absKnob < 450) {
         setSpeed(&sm,15);
         if (knob > 0) {
            turnOnLed(LED3);
            turnCCWStepperMotor(&sm);
         } else {
            turnOnLed(LED1);
            turnCWStepperMotor(&sm);
         }

      } else {
         setSpeed(&sm,5);
         if (knob > 0) {
            turnOnLed(LED3);
            turnCCWStepperMotor(&sm);
         } else {
            turnOnLed(LED1);
            turnCWStepperMotor(&sm);
         }
      }
       update(&sm);


        // pc interaction
      cmd = uartReadByte(UART_USB);
      if (cmd) {
         switch (cmd) {
         case 'A':
         case 'a':
              updateAnalogReadMessage(knob);
              uartWriteString(UART_USB,msgAnalogRead);
              break;
         case 'R':
         case 'r':
            turnOnLed(LEDR);
            sayLedOn('r');
            break;
         case 'G':
         case 'g':
            turnOnLed(LEDG);
            sayLedOn('g');
            break;
         case 'B':
         case 'b':
            turnOnLed(LEDB);
            sayLedOn('b');
            break;
         case '0':
            turnOffRGB();
            sayLedOn('0');
            break;


         default:
            showMenu();
            break;
         }
      }

   }
   return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

