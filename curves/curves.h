#ifndef CURVES_H
#define CURVES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdint.h>

// ; m = ( y2 - y1) / (x2 - x1)
// ; rdi = x2 - x1 & rsi = y2 - y1 

uint64_t slope(uint64_t y2, uint64_t y1, uint64_t x2, uint64_t x1);

//  ; x_3 = m^2 - x1 - x2
uint64_t slopevalx(uint64_t slope, uint64_t x1, uint64_t x2);
//  ; y_3 = m * (x1 - x3) - y1
uint64_t slopevaly(uint64_t slope, uint64_t x1, uint64_t x3, uint64_t y1);

#endif