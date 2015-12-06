#include "Rcc.h"
#include "stm32f4xx_hal_rcc.h"
#include "Gpio.h"

void gpioUnresetEnableClock(GPIO *port){
	uint32_t checkRSTR;
	uint32_t checkENR;
	int valToShift = ((int)port - (0x40020000))/(0x400);
	RCC_reg->AHB1RSTR &= ~(1 << (valToShift));
	RCC_reg->AHB1ENR |= (0x00100000 | (1 << (valToShift)));
	checkRSTR = RCC_reg->AHB1RSTR ;
	checkENR = RCC_reg->AHB1ENR;
}

uint32_t getSystemClock(){
 int divM,divP,divAHB,xN;
 int sysClock;
 int clockSW;
 int pllSW;
 int divAHBList[] ={1,1,1,1,1,1,1,1,\
		            2,4,8,16,64,128,256,512};
 int divPList[] = {2,4,6,8};
 divAHB = divAHBList[ (RCC_reg->CFGR >> 4) & 0xF ];
 divP = divPList[ (RCC_reg->PLLCFGR >> 16) & 3 ];
 divM = RCC_reg->PLLCFGR & 63;
 xN = (RCC_reg->PLLCFGR >> 6) & 511;
 clockSW = (RCC_reg->CFGR >> 2) & 3 ;
 if(clockSW == 0){
   sysClock = HSI_VALUE / divAHB;
 }else if(clockSW == 1){
   sysClock = HSE_VALUE / divAHB;
 }else{
  pllSW = (RCC_reg->PLLCFGR >> 22) & 1;
  if(pllSW){
	  sysClock = (HSI_VALUE * xN) / (divM * divP * divAHB);
  }else{
	  sysClock = (HSE_VALUE) / (divM * divP * divAHB) * xN;
  }
 }
 return sysClock;
}

uint32_t getAHB2Clock( uint32_t sysClock){


}


