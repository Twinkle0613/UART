#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "Gpio.h"
//#include "stdint.h"
#include "Rcc.h"
#include "UART.h";


uint8_t byleButter;
void delay(uint32_t delayCount){
  while(delayCount != 0 ){
	delayCount--;
  }
}

/*
 


*/


void UART5_IRQHandler(){
	int noise,framErr,parErr,overRunErr;

	if(readyTransmit){
	  sendByle('F');
	}

	if(readyReceived){
	   checkUART5err(&noise,&framErr,&parErr,&overRunErr);
	  if(!overRunErr && !framErr && !parErr && !noise){
	    byleButter = receivedByle();
	  }else{
	    handleUART5err();
	  }
	}
	clearInterruptFlag();
}


int main(){
	HAL_NVIC_EnableIRQ(UART5_IRQn);
    configureAlterFuncPin(2,PORTD,8);   //RX PD2
    configureAlterFuncPin(12,PORTC,8);  //TX PC12
	configureOutPin(GPIO_MODE_OUTPUT,PIN_14,PORTG); // for LD14
	configureOutPin(GPIO_MODE_OUTPUT,PIN_13,PORTG); // for LD14
    configureUART(UART5,9600,UART_PARITY_DISABLE,UART_STOPBITS_1,UART_WORDLENGTH_8B);
    congifureUART_IE(UART5,TX_EMPTY_ID,TX_COMPLETE_ID,RX_NOT_EMPTY_IE,PARITY_ID,ERROR_ID);
    uint8_t butter;
    uint32_t checkSR;
    int noise,framErr,parErr,overRunErr;
    int i = 0;
    int rxne = getUART5Status(FLAG_RXNE);
 while(1){
	 writeSet(PORTG,14);
	 if(!i){
	 sendByle('F');
	 sendByle('H');
	 sendByle('3');
	 i = ~i;
	 }else {
	 sendByle('F');
	 i = ~i;
	 }

    // delay(10000000);
/*
   if( readyReceived ){ // receiver received data.
	 checkSR = UART5->SR ;
	 checkUART5err(&noise,&framErr,&parErr,&overRunErr);
	 if(!overRunErr && !framErr && !parErr && !noise){
	  butter = receivedByle();
      writeSet(PORTG,13);
	 }else{
	  handleUART5err();
	 }
   }
*/
   rxne = getUART5Status(FLAG_RXNE);
   writeReset(PORTG,13);
   checkSR = UART5->SR ;
 }


}
