#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "Gpio.h"
//#include "stdint.h"
#include "Rcc.h"
#include "UART.h";

void delay(uint32_t delayCount){
  while(delayCount != 0 ){
	delayCount--;
  }
}

void UART5_IRQHandler(){
   
   //if( getBit(UART5->SR,RXNE) ){
   //  getData(readStr);
   //}
   
   
   
   //UART5->SR = 0;  //clear status
}
HAL_NVIC_EnableIRQ(UART5_IRQn);

int main(){
    configureAlterFuncPin(2,PORTD,8);   //RX PD2
    configureAlterFuncPin(12,PORTC,8);  //TX PC12
	configureOutPin(GPIO_MODE_OUTPUT,PIN_14,PORTG); // for LD14
	configureOutPin(GPIO_MODE_OUTPUT,PIN_13,PORTG); // for LD14
    configureUART(UART5,9600,UART_PARITY_DISABLE,UART_STOPBITS_1,UART_WORDLENGTH_8B);

    uint8_t butter;
    uint32_t checkSR;
    int checkPCLK1 = HAL_RCC_GetPCLK1Freq();
    int checkPCLK2 = HAL_RCC_GetPCLK2Freq();
 while(1){
	 writeSet(PORTG,14);
	 sendByle('F');
     delay(10000000);

   if( readyReceived() ){ // receiver received data.
	 checkSR = UART5->SR ;
	 butter = receivedByle();
     writeSet(PORTG,13);
   }
   writeReset(PORTG,13);
   checkSR = UART5->SR ;
 }


}
