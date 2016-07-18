#ifndef _FSM_KEYREADER_H_
#define _FSM_KEYREADER_H_


#include "stdint.h"

typedef enum {UP=0, FALLING, DOWN, RISING} STATE;

struct buttons_t {
	int button;
	STATE state;
	int buttonName;
	uint8_t hasChanged;
};

struct fsm_keyReader_t {
	struct buttons_t buttons[4];
};

struct fsm_keyReader_t createFsmKeyReader();

int readKeys(struct fsm_keyReader_t * kr);

uint8_t keyHasChanged(struct fsm_keyReader_t * kr, uint8_t idx);

uint8_t keyIsPressed(struct fsm_keyReader_t * kr, uint8_t idx);

#endif // _FSM_KEYREADER_H_
