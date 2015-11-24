#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "Gpio.h"
//#include "stdint.h"
#include "Rcc.h"


// void HASH_UART5_IRQHandler(){
	// int status = RNG_reg->RNG_SR;
	// if(status == 1)
		// randomValue = RNG_reg->RNG_DR;
	// else
		// RNG_reg->RNG_SR = 0;

	// entered++;

// }

int main(){
    gpioUnresetEnableClock(PORTC);
    gpioUnresetEnableClock(PORTD);
    configureIntPin(GPIO_MODE_INPUT,2,PORTD); // RX PD2
    configurePin(GPIO_MODE_OUTPUT,12,PORTC);  // TX PC12
    configureUART(UART5);
    uartUnresetEnableClock();

 while(1){

 
 
 }


}
