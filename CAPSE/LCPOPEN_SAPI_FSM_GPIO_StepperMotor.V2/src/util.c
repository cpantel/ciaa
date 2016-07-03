#include "util.h"


int abs(const int value) {
   return ( value & 0x80000000 );
}

uint8_t * itoa(int number, uint8_t buffer[], const int base) {

   static uint8_t map[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVW";
   int size = 32;
   int remainder;
   int error = 0;
   int idx;
   int idy = 0;

   // check buffer length is 33 and zero it
   for ( idx = 0; idx < ( size + 1) ; idx++) {
       if (buffer[idx] == 0) {
          error = 1;
          break;
       }
       buffer[idx] = 0;
   }
   // check buffer is zero terminated
   if (buffer[size + 1] != 0) {
      error = 2;
   }

   // check base between 2 and 32
   if ( base < 2 || base > size ) {
      error = 3;
   }
   if ( error != 0) {
      buffer[0] = 0;
   } else {
      if ( number < 0 ) {
         buffer[0]='-';
         idy = 1;
         number = -number;
      }
      idx = size - 1;
      while (number > 0) {
         remainder = number % base;
         buffer[idx] = map[remainder];
         idx--;
         number = (number - remainder ) / base;
      }
      idx++;
      for ( ; idx < 34; idx++, idy++) {
          buffer[idy] = buffer[idx];
      }
   }
   return buffer;
}
