#ifndef BaudRateAlgorithm_H
#define BaudRateAlgorithm_H
#include "stdint.h"
uint32_t roundOff(float floatNumber);
void baudRateSetting(int baudRate,int fpclk, uint32_t* pgmValue);
#endif // BaudRateAlgorithm_H
