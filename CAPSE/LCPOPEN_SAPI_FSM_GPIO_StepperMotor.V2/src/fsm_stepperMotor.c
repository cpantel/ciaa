#include "fsm_stepperMotor.h"
#include "sAPI.h"



void turnOnPin0(struct fsm_StepperMotor_t * sm) {
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO0_GPIO_PORT,DIO0_GPIO_PIN,ON);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO2_GPIO_PORT,DIO2_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO4_GPIO_PORT,DIO4_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO6_GPIO_PORT,DIO6_GPIO_PIN,OFF);
}

void turnOnPin2(struct fsm_StepperMotor_t * sm) {
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO0_GPIO_PORT,DIO0_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO2_GPIO_PORT,DIO2_GPIO_PIN,ON);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO4_GPIO_PORT,DIO4_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO6_GPIO_PORT,DIO6_GPIO_PIN,OFF);
}

void turnOnPin4(struct fsm_StepperMotor_t * sm) {
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO0_GPIO_PORT,DIO0_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO2_GPIO_PORT,DIO2_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO4_GPIO_PORT,DIO4_GPIO_PIN,ON);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO6_GPIO_PORT,DIO6_GPIO_PIN,OFF);
}

void turnOnPin6(struct fsm_StepperMotor_t * sm) {
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO0_GPIO_PORT,DIO0_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO2_GPIO_PORT,DIO2_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO4_GPIO_PORT,DIO4_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO6_GPIO_PORT,DIO6_GPIO_PIN,ON);
}

void turnOffPins(struct fsm_StepperMotor_t * sm) {
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO0_GPIO_PORT,DIO0_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO2_GPIO_PORT,DIO2_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO4_GPIO_PORT,DIO4_GPIO_PIN,OFF);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO6_GPIO_PORT,DIO6_GPIO_PIN,OFF);
}

void turnPinsOn(struct fsm_StepperMotor_t * sm) {
   switch (sm->stepMap[sm->step]) {
      case STEP_0: turnOnPin0(sm); break;
      case STEP_2: turnOnPin2(sm); break;
      case STEP_4: turnOnPin4(sm); break;
      case STEP_6: turnOnPin6(sm); break;
      default:
         uartWriteString(UART_USB,"BAD state\n\r");
   }
   return;
}

void microTurnPinsOn(struct fsm_StepperMotor_t * sm) {

//   int value0 = step & 1;
//   int value2 = step & 2;
//   int value4 = step & 4;
//   int value6 = step & 8;
   uint8_t value0 = sm->stepMap[sm->step] & 1;
   uint8_t value2 = sm->stepMap[sm->step] & 2;
   uint8_t value4 = sm->stepMap[sm->step] & 4;
   uint8_t value6 = sm->stepMap[sm->step] & 8;
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO0_GPIO_PORT,DIO0_GPIO_PIN,value0);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO2_GPIO_PORT,DIO2_GPIO_PIN,value2);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO4_GPIO_PORT,DIO4_GPIO_PIN,value4);
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIO6_GPIO_PORT,DIO6_GPIO_PIN,value6);
}

void turnLeftStepperMotor(struct fsm_StepperMotor_t * sm) {
   int b;
   int a = 25;
   for (b=0; b<10; b++) {
      turnOnPin0(sm);
      delay(a);
      turnOnPin2(sm);
      delay(a);
      turnOnPin4(sm);
      delay(a);
      turnOnPin6(sm);
      delay(a);
   }
   turnOffPins(sm);
}

void turnRightStepperMotor(struct fsm_StepperMotor_t * sm) {
   int b;
   int a = 25;
   for (b=0; b<10; b++) {
      turnOnPin6(sm);
      delay(a);
      turnOnPin4(sm);
      delay(a);
      turnOnPin2(sm);
      delay(a);
      turnOnPin0(sm);
      delay(a);
   }
   turnOffPins(sm);
}

struct fsm_StepperMotor_t createFsmStepperMotor() {
   Chip_SCU_PinMux(DIO0_SCU_PORT,DIO0_SCU_PIN,MODE_OUTPUT, DIO0_FUNC);
   Chip_GPIO_SetDir(LPC_GPIO_PORT,DIO0_GPIO_PORT,(1 << DIO0_GPIO_PIN),OUTPUT);

   Chip_SCU_PinMux(DIO2_SCU_PORT,DIO2_SCU_PIN,MODE_OUTPUT, DIO2_FUNC);
   Chip_GPIO_SetDir(LPC_GPIO_PORT,DIO2_GPIO_PORT,(1 << DIO2_GPIO_PIN),OUTPUT);

   Chip_SCU_PinMux(DIO4_SCU_PORT,DIO4_SCU_PIN,MODE_OUTPUT, DIO4_FUNC);
   Chip_GPIO_SetDir(LPC_GPIO_PORT,DIO4_GPIO_PORT,(1 << DIO4_GPIO_PIN),OUTPUT);

   Chip_SCU_PinMux(DIO6_SCU_PORT,DIO6_SCU_PIN,MODE_OUTPUT, DIO6_FUNC);
   Chip_GPIO_SetDir(LPC_GPIO_PORT,DIO6_GPIO_PORT,(1 << DIO6_GPIO_PIN),OUTPUT);
    delay_t delay;
   struct fsm_StepperMotor_t sm = {
      //{0,0,0},
      delay,
       STOPPED,
       { STEP_0, STEP_02, STEP_2, STEP_24, STEP_4, STEP_46, STEP_6, STEP_60 },
       //{ STEP_0,  STEP_2,  STEP_4,  STEP_6 },
       STEP_0,
       1000
    };

    turnLeftStepperMotor(&sm);
    turnRightStepperMotor(&sm);
    turnOffPins(&sm);
    delayConfig(&(sm.delay),sm.speed);

    return sm;
}

void stopStepperMotor(struct fsm_StepperMotor_t * sm) {
   sm->state = STOPPED;
}

void releaseStepperMotor(struct fsm_StepperMotor_t * sm) {
   turnOffPins(sm);
   sm->state = FREE;
}



void setSpeed(struct fsm_StepperMotor_t * sm, int speed) {
   sm->speed = speed;
}

int increaseSpeed(struct fsm_StepperMotor_t * sm) {
   return 0;
}

int decreaseSpeed(struct fsm_StepperMotor_t * sm) {
   return 0;
}


void updateStepperMotor(struct fsm_StepperMotor_t * sm) {
   switch ( sm->state ) {
   case FREE:
   case STOPPED:
      return;
      break;
   case CLOCKWISE:
   case COUNTERCLOCKWISE:
      if (delayRead(&(sm->delay))) {
           if (sm->state == CLOCKWISE) {
              sm->step++;
              if (sm->step == 8) {  // count of states
                 sm->step = 0;
              }
           } else {
              sm->step--;
              if (sm->step == 255 ) {
                 sm->step = 7;     // last state
              }
           }
//           uint8_t buffer[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVW";
//           itoa(sm->stepMap[sm->step], buffer, 10);
//          uartWriteString(UART_USB,"step: ");
//          uartWriteString(UART_USB,buffer);
//          uartWriteString(UART_USB,"\n\r");

            microTurnPinsOn(sm);
           delayWrite(&(sm->delay),sm->speed);
      }

       break;
   default:
   break;
   }
}

void turnCWStepperMotor(struct fsm_StepperMotor_t * sm) {
   if (sm->state != CLOCKWISE) {
     delayWrite(&(sm->delay),sm->speed);
     sm->state = CLOCKWISE;
   }
}

void turnCCWStepperMotor(struct fsm_StepperMotor_t * sm) {
   if (sm->state != COUNTERCLOCKWISE) {
      delayWrite(&sm->delay,sm->speed);
      sm->state = COUNTERCLOCKWISE;
   }

}


