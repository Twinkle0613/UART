#include "BaudRateAlgorithm.h"
#include "stdint.h"
//#include "stdlib.h"

uint32_t baudRateSetting(int baudRate,int fpclk){
  uint32_t pgmValue;
  float DIV;
  uint32_t mantissa;
  uint32_t fraction;
  float floatNumber;
  int int2;
  int intNumber;

  DIV = ((float)fpclk )/( ((float)baudRate ) *8);
  mantissa = (uint32_t)DIV;
  floatNumber = ( DIV - mantissa ) * 8;
  fraction = roundOff(floatNumber);
  if(fraction > 7 ){
   fraction = 7;
  }
  pgmValue = ( (mantissa << 4 ) | fraction ) & 0x0000FFFF;
  return pgmValue;
}

uint32_t baudRateAlgorithm(int baudRate,int fpclk,int Over8){
  uint32_t pgmValue;
  float DIV;
  uint32_t mantissa;
  uint32_t fraction;
  float floatNumber;
  int int2;
  int intNumber;
  if(Over8){

   DIV = ((float)fpclk )/( ((float)baudRate ) *8);
   floatNumber = ( DIV - mantissa ) * 8;
   fraction = roundOff(floatNumber);
   if(fraction > 7 ){
    fraction = 7;
   }

  }else{

   DIV = ((float)fpclk )/( ((float)baudRate ) *16);
   floatNumber = ( DIV - mantissa ) * 16;
   fraction = roundOff(floatNumber);
   if(fraction > 15 ){
	 fraction = 15;
   }

  }
  mantissa = (uint32_t)DIV;

  pgmValue = ( (mantissa << 4 ) | fraction ) & 0x0000FFFF;
  return pgmValue;
}


uint32_t roundOff(float floatNumber){
  uint32_t int0;
  uint32_t int1;
  uint32_t int2;
  uint32_t int3;

  int0 = floatNumber;
  int1 = int0 * 10;
  int2 = floatNumber * 10;
  int3 = int2 - int1;

  if(int3 >= 5 ){
   return int0+1;
  }
   return int0;
  
}

