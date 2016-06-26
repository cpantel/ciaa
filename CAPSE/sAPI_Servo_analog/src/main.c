/* 
 *  servo en donde va pwm0
 */

#include "main.h"

#include "sAPI.h"

int main(void)
{
   boardConfig();

   tickConfig( 1, 0 );

   servoConfig( 0,      ENABLE_SERVO_TIMERS );

   servoConfig( SERVO0, ENABLE_SERVO_OUTPUT );

   servoWrite( SERVO0, 0 );

   analogConfig( ENABLE_ANALOG_INPUTS );

   while(1) {
      int knob = analogRead(AI1);
      servoWrite( SERVO0, knob * 180 / 1024 );
      delay(50);
   }
  return 0 ;
}
