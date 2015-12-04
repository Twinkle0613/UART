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
