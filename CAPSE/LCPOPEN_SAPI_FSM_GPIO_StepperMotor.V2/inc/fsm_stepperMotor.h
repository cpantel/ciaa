#ifndef _fsm_steppermotor_h_
#define _fsm_steppermotor_h_

#include "chip.h"
#include "sAPI.h"

#define DIO0_SCU_PORT   6
#define DIO0_SCU_PIN    1
#define DIO0_FUNC       FUNC0
#define DIO0_GPIO_PORT  3
#define DIO0_GPIO_PIN   0

#define DIO2_SCU_PORT   6
#define DIO2_SCU_PIN    5
#define DIO2_FUNC       FUNC0
#define DIO2_GPIO_PORT  3
#define DIO2_GPIO_PIN   4

#define DIO4_SCU_PORT   6
#define DIO4_SCU_PIN    8
#define DIO4_FUNC       FUNC4
#define DIO4_GPIO_PORT  5
#define DIO4_GPIO_PIN   16

#define DIO6_SCU_PORT   6
#define DIO6_SCU_PIN    10
#define DIO6_FUNC       FUNC0
#define DIO6_GPIO_PORT  3
#define DIO6_GPIO_PIN   6

#define MODE_OUTPUT     (SCU_MODE_INACT | SCU_MODE_ZIF_DIS )
#define MODE_INPUT      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_INBUFF_EN )

typedef enum { CLOCKWISE, COUNTERCLOCKWISE, STOPPED, FREE } DIRECTION;
typedef enum {
	STEP_0  = 0b0001,
	STEP_02 = 0b0011,
	STEP_2  = 0b0010,
	STEP_24 = 0b0110,
	STEP_4  = 0b0100,
	STEP_46 = 0b1100,
	STEP_6  = 0b1000,
	STEP_60  = 0b1001
} STEPS;

//typedef enum {
//	Stepper_0  = 0b0001,
//	Stepper_02 = 0b0011,
//	Stepper_2  = 0b0010,
//	Stepper_24 = 0b0110,
//	Stepper_4  = 0b0100,
//	Stepper_46 = 0b1100,
//	Stepper_6  = 0b1000,
//	Stepper_60 = 0b1001
//} StepperS;

struct fsm_StepperMotor_t {
	delay_t delay;
	DIRECTION state;
	STEPS stepMap[8];
	uint8_t step;
    int speed;
};


struct fsm_StepperMotor_t createFsmStepperMotor();
void stopStepperMotor(struct fsm_StepperMotor_t * sm);
void releaseStepperMotor(struct fsm_StepperMotor_t * sm);
void turnCWStepperMotor(struct fsm_StepperMotor_t * sm);
void turnCCWStepperMotor(struct fsm_StepperMotor_t * sm);
void setSpeed(struct fsm_StepperMotor_t * sm, int speed);
int increaseSpeed(struct fsm_StepperMotor_t * sm);
int decreaseSpeed(struct fsm_StepperMotor_t * sm);
void turnOnPin0(struct fsm_StepperMotor_t * sm);
void turnOnPin2(struct fsm_StepperMotor_t * sm);
void turnOnPin4(struct fsm_StepperMotor_t * sm);
void turnOnPin6(struct fsm_StepperMotor_t * sm);
void updateStepperMotor(struct fsm_StepperMotor_t * sm);



#endif //  _fsm_steppermotor_h_
