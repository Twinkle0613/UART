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


void UART5_IRQHandler(){
	int noise,framErr,parErr,overRunErr;
	uint8_t butter;
	checkUART5err( &noise,&framErr,&parErr,&overRunErr );
	handleUART5ErrInInterrupt();
	if( readyTransmit && enableTXEIE ){
		sendByle('H');
	}
	if( completeTransmit && enableTCIE ){

	}
	if( readyReceived && enableRXNEIE){
	   butter = receivedByle();
	}
	clearInterruptFlag();
}


int main(){
	HAL_NVIC_EnableIRQ(UART5_IRQn);
    configureAlterFuncPin(2,PORTD,8);   //RX PD2
    configureAlterFuncPin(12,PORTC,8);  //TX PC12
	configureOutPin(GPIO_MODE_OUTPUT,PIN_14,PORTG); // for LD14
	configureOutPin(GPIO_MODE_OUTPUT,PIN_13,PORTG); // for LD14
    configureUART(UART5,9600,UART_PARITY_ENABLE,UART_STOPBITS_1,UART_WORDLENGTH_8B);
    congifureUART_IE(UART5,TX_EMPTY_ID,TX_COMPLETE_ID,RX_NOT_EMPTY_IE,PARITY_IE,ERROR_ID);
    uint8_t butter;
    uint32_t checkSR;
    int noise,framErr,parErr,overRunErr;
    int i= 0;
 //   uint32_t sysClk  = getSystemClock();
    uint32_t RCCcfgr = RCC_reg->CFGR;
 while(1){
	//sendByle('F');
	//sendByle('H');
	//sendByle('H');
	//sendByle('J');
     putData("JH");
//	 delay(1000000);
	//checkUART5err(&noise,&framErr,&parErr,&overRunErr);
	//handleUART5err();
	//if( readyReceived ){
	// butter  = receivedByle();
	//	butter  = receivedByle();
	//}
 }

}

// delay(10000000);
/*
if(!i){
sendBreak();
i = ~i;
}else{
stopBreak();
i = ~i;
}
*/
