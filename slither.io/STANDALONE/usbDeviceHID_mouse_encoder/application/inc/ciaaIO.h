/*
 * ciaaIO.h
 *
 *  Created on: Jun 12, 2014
 *      Author: pablo
 */

#ifndef CIAAIO_H_
#define CIAAIO_H_

#include "chip.h"

#define ciaaDigitalInputs() ((uint8_t)((Chip_GPIO_ReadValue(LPC_GPIO_PORT,3) & (0x0F<<11))>>7)|(Chip_GPIO_ReadValue(LPC_GPIO_PORT,2) & 0x0F))

typedef struct
{
	int port;
	int bit;
}ciaaPin_t;

void ciaaIOInit(void);
uint32_t ciaaWriteOutput(uint32_t outputNumber, uint32_t value);
uint32_t ciaaReadInput(uint32_t inputNumber);
void ciaaToggleOutput(uint32_t outputNumber);

#endif /* CIAAIO_H_ */
