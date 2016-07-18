#include "fsm_keyReader.h"

#include "sAPI.h"         /* <= sAPI header */

struct fsm_keyReader_t createFsmKeyReader() {
   // fsm_keyReader
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );


    struct fsm_keyReader_t keyReader = {
       {
          { TEC1, UP,  1, 0},
          { TEC2, UP,  2, 0},
          { TEC3, UP,  3, 0},
          { TEC4, UP,  4, 0}
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

int readKeys(struct fsm_keyReader_t * kr) {
   uint8_t idx;
   uint8_t pendingTransition = 1;
    uint8_t pressed;

    while (pendingTransition) {
      pendingTransition--;
      for ( idx = 0; idx < 4; idx ++) {
         kr->buttons[idx].hasChanged = 0;
         pressed = ! digitalRead( kr->buttons[idx].button );

         switch (kr->buttons[idx].state) {
            case UP: {
               if (pressed) {
                  kr->buttons[idx].state = FALLING;
                  pendingTransition++;
               }
               break;
            }
            case FALLING: {
               if (pressed) {
                  kr->buttons[idx].state = DOWN;
                  kr->buttons[idx].hasChanged = 1;
               } else {
                  kr->buttons[idx].state = UP;
               }
               break;
            }
            case DOWN: {
               if (! pressed) {
                  kr->buttons[idx].state = RISING;
                  pendingTransition++;
               }
               break;
            }
            case RISING: {
               if (! pressed) {
                  kr->buttons[idx].state = UP ;
                  kr->buttons[idx].hasChanged = 1;
               } else {
                  kr->buttons[idx].state = DOWN;
               }
               break;
            }
            default: {
               kr->buttons[idx].state = UP;
            }
         }
      }
      if (pendingTransition) {
         delay(40);
      }
    }
   return 0;
}
