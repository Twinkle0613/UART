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
//HAL_NVIC_EnableIRQ(UART5_IRQn);

int main(){

    configureAlterFuncPin(2,PORTD,8);   //RX PD2
    configureAlterFuncPin(12,PORTC,8);  //TX PC12
	configureOutPin(GPIO_MODE_OUTPUT,PIN_14,PORTG); // for LD14
	configureOutPin(GPIO_MODE_OUTPUT,PIN_13,PORTG); // for LD14
    configureUART(UART5,9600,UART_PARITY_DISABLE,UART_STOPBITS_1,UART_WORDLENGTH_8B);
    uint8_t butter[25];
    uint32_t checkSR;
 while(1){
	 writeSet(PORTG,14);

     putData("HJK");  // keep do it send data
     UART5->SR = checkSR;
   if( getUART5StatusBit(RXNE) ){ // receiver received data.
	   UART5->SR = checkSR;
	   writeSet(PORTG,13);
	   getData(butter);
   }
   writeReset(PORTG,13);
   UART5->SR = checkSR;
 }


}
