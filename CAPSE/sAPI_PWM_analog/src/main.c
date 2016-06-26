/* 
 *   pote en AI1 ()
 *
 *   osciloscopio en pwm0 ()
 */

#include "main.h"

#include "sAPI.h"

bool_t myTickHook(void *ptr){

   digitalWrite( LEDG, 1 );

   return 1;
}

int main(void)
{
   boardConfig();

   tickConfig( 1, 0 );

   digitalConfig( 0, ENABLE_DIGITAL_IO );


   uint8_t dutyCycle = 0; /* 0 a 255 */

   analogConfig( ENABLE_ANALOG_INPUTS );

   pwmConfig( 0,     PWM_TIMERS_ENABLE );

   pwmConfig( PWM0,  PWM_OUTPUT_ENABLE );
   pwmConfig( PWM7,  PWM_OUTPUT_ENABLE );

   pwmWrite( PWM7, 0 );
   pwmWrite( PWM0, 0 );

   while(1) {
      dutyCycle = analogRead(AI1) / 4 ;
      pwmWrite( PWM7, dutyCycle );
      pwmWrite( PWM0, dutyCycle );
   }
   return 0 ;
}
