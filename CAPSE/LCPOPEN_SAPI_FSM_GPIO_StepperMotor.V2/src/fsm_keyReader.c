#include "fsm_keyReader.h"

#include "sAPI.h"         /* <= sAPI header */

struct fsm_keyReader_t createFsmKeyReader() {
   // fsm_keyReader
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );

   delay_t delay;

    struct fsm_keyReader_t keyReader = {
       {
          { delay, TEC1, UP,  1, 0},
          { delay, TEC2, UP,  2, 0},
          { delay, TEC3, UP,  3, 0},
          { delay, TEC4, UP,  4, 0}
       }
    };
    return keyReader;
}


uint8_t keyHasChanged(struct fsm_keyReader_t * kr, uint8_t idx) {
   uint8_t hasChanged = kr->buttons[idx - 1].hasChanged;
   kr->buttons[idx - 1].hasChanged = 0;
   return hasChanged;
}

uint8_t keyIsPressed(struct fsm_keyReader_t * kr, uint8_t idx) {
   return ( kr->buttons[idx - 1].state == DOWN);
}

void updateKeyReader(struct fsm_keyReader_t * kr) {
   uint8_t idx;
   uint8_t pendingTransition = 1;
    uint8_t pressed;

   for ( idx = 0; idx < 4; idx ++) {
      kr->buttons[idx].hasChanged = 0;
      pressed = ! digitalRead( kr->buttons[idx].button );

      switch (kr->buttons[idx].state) {
         case UP: {
            if (pressed) {
               kr->buttons[idx].state = FALLING;
               delayWrite(&(kr->buttons[idx].delay), EDGE_DELAY);
               //pendingTransition++;
            }
            break;
         }
         case FALLING: {
            if (delayRead(&(kr->buttons[idx].delay))) {
               if (pressed) {
                  kr->buttons[idx].state = DOWN;
                  kr->buttons[idx].hasChanged = 1;
               } else {
                  kr->buttons[idx].state = UP;
               }
            }
            break;
         }
         case DOWN: {
            if (! pressed) {
               kr->buttons[idx].state = RISING;
               delayWrite(&(kr->buttons[idx].delay), EDGE_DELAY);
            }
            break;
         }
         case RISING: {
            if (delayRead(&(kr->buttons[idx].delay))) {
               if (! pressed) {
                  kr->buttons[idx].state = UP ;
                  kr->buttons[idx].hasChanged = 1;
               } else {
                  kr->buttons[idx].state = DOWN;
               }
            }
            break;
         }
         default: {
            kr->buttons[idx].state = UP;
         }
      }

    }
}
