#ifndef BaudRateAlgorithm_H
#define BaudRateAlgorithm_H
#include "stdint.h"
uint32_t roundOff(float floatNumber);
uint32_t baudRateSetting(int baudRate,int fpclk);
uint32_t baudRateAlgorithm(int baudRate,int fpclk,int Over8);

#endif // BaudRateAlgorithm_H
