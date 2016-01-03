#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "Gpio.h"
//#include "stdint.h"
#include "Rcc.h"
#include "UART.h";
#include "DMA.h"

uint8_t rxBuffer[255];
uint8_t txBuffer[] = "HIJK";

//"NwaNeng,Here!"
void delay(uint32_t delayCount){
  while(delayCount != 0 ){
	delayCount--;
  }
}
void DMA1_Stream0_IRQHandler(){
	clearDMAFlag(DMA1,STREAM0,FLAG_TCIF0);
}

//int noise,framErr,parErr,overRunErr;
//checkUART5err( &noise,&framErr,&parErr,&overRunErr );
//uint32_t checkRXbuffer;
//uint32_t checkNDTR = DMA1->S0.NDTR;
//if(compReceiveRX)
//	checkRXbuffer = rxBuffer[0];
//clearDMAFlag(DMA1,STREAM0,FLAG_TCIF0);

void DMA1_Stream7_IRQHandler(){
	clearDMAFlag(DMA1,STREAM7,FLAG_TCIF7);
}
//checkUART5err( &noise,&framErr,&parErr,&overRunErr );
//handleUART5ErrInInterrupt();
//int noise,framErr,parErr,overRunErr;
//uint8_t butter;

void UART5_IRQHandler(){
	if( readyTransmit && enableTXEIE ){
	  sendStringByInterrupt("NwaNeng,Here!");
	}
	if( readyReceived && enableRXNEIE){
	  getStringByInterrupt(rxBuffer,13);
	}
	clearInterruptFlag();
}


int main(){
	HAL_NVIC_EnableIRQ(UART5_IRQn);
	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);

	configureDMA(DMA1,0,CHANNEL4,PERIPHERAL_TO_MEMORY,BYTE,BYTE,&(UART5->DR),rxBuffer,4); //RX
	configureDMA(DMA1,7,CHANNEL4,MEMORY_TO_PERIPHERAL,BYTE,BYTE,txBuffer,&(UART5->DR),4); //TX

	configureAlterFuncPin(2,PORTD,8);   //RX PD2
    configureAlterFuncPin(12,PORTC,8);  //TX PC12

    configureOutPin(GPIO_MODE_OUTPUT,PIN_14,PORTG); // for LD14
    configureOutPin(GPIO_MODE_OUTPUT,PIN_13,PORTG); // for LD14

    configureUART(UART5,115200,UART_PARITY_DISABLE,UART_STOPBITS_1,UART_WORDLENGTH_8B);

    uartEnableDMA(UART5);
    congifureUART_IE(UART5,TX_EMPTY_ID,TX_COMPLETE_ID,RX_NOT_EMPTY_ID,PARITY_ID,ERROR_ID);
    uint8_t butter;
    int noise,framErr,parErr,overRunErr;
   uint32_t checkDMA1HISR,checkRXbuffer;
   uint32_t checkDMA1LISR;
   uint32_t checkUARTDR;
   enableDmaTX(DMA1);
   enableDmaRX(DMA1);
 while(1){
	 writeReset(PORTG,PIN_14);
	 writeSet(PORTG,PIN_13);
	 delay(10000000);
	 writeSet(PORTG,PIN_14);
	 writeReset(PORTG,PIN_13);
	 delay(10000000);
 }
}

/*
	 writeReset(PORTG,PIN_14);
	 writeSet(PORTG,PIN_13);
	 delay(10000000);
	 writeSet(PORTG,PIN_14);
	 writeReset(PORTG,PIN_13);
	 delay(10000000);
*/

// checkUART5err( &noise,&framErr,&parErr,&overRunErr );

 //handleUART5err();
// if(readyReceived ){
//	butter = receivedByle();
//	butter = receivedByle();
// }
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
