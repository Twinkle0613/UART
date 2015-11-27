#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "Gpio.h"
//#include "stdint.h"
#include "Rcc.h"
#include "UART.h";



void UART5_IRQHandler(){
   
   //if( getBit(UART5->SR,RXNE) ){
   //  getData(readStr);
   //}
   
   
   
   //UART5->SR = 0;  //clear status
}


int main(){

    //HAL_NVIC_EnableIRQ(UART5_IRQn);
	configurePin(GPIO_MODE_OUTPUT,PIN_14,PORTG); // for LD14
    //configurePin(GPIO_MODE_OUTPUT,PIN_13,PORTG); // for LD13

    gpioUnresetEnableClock(PORTC);
    gpioUnresetEnableClock(PORTD);
    configureIntPin(GPIO_MODE_INPUT,2,PORTD);    // RX PD2
    configureOutPin(GPIO_MODE_OUTPUT,12,PORTC);  // TX PC12
    configureUART(UART5,9600,UART_PARITY_DISABLE,UART_STOPBITS_1,UART_WORDLENGTH_8B);
    uartUnresetEnableClock();
    uint8_t butter[25];
 while(1){

   putData("Hello World");  // keep do it send data
   if( getUART5StatusBit(RXNE) ){ // check the receive flag
	   writeSet(PORTG,14);
	   getData(butter);
	   printf("%s\n", butter);
   }
   writeReset(PORTG,14);

 }


}
