#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "Gpio.h"
//#include "stdint.h"
#include "Rcc.h"



void UART5_IRQHandler(){




}


int main(){

	HAL_NVIC_EnableIRQ(UART5_IRQn);
    gpioUnresetEnableClock(PORTC);
    gpioUnresetEnableClock(PORTD);
    configureIntPin(GPIO_MODE_INPUT,2,PORTD); // RX PD2
    configureOutPin(GPIO_MODE_OUTPUT,12,PORTC);  // TX PC12
    configureUART(UART5);
    uartUnresetEnableClock();

 while(1){

 
 
 }


}
