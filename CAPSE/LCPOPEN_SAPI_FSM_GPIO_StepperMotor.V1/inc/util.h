#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdint.h"

int abs(const int value);

uint8_t * itoa(int number, uint8_t buffer[], const int base);

#endif // _UTIL_H_
