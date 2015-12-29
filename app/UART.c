#include "UART.h"
#include "Rcc.h"
#include "BaudRateAlgorithm.h"
#include "stdlib.h"




/*
 *  ----Documentation----
 *  The configuration can be separate in three of part such as RCC,GPIO and UART.
 *
 *  The UART5 is used to communicate with another peripherals in to this project.
 *  To study transmit and received process.
 *   The transmitter pin of UART5 is pin 12 of port C(PC12).
 *   The receiver pin of UART5 is pin 2 of port D (PD2).
 *
 *  configuration in GPIO
 *   - enable PORTD and PORTC
 *
 *  configuration in RCC
 *   - enable the clock of UART5 in UART5_EN (bit 20) of RCC_APB1ENR
 *   - disable the reset of UART5 in UART5_RST(bit 20) of RCC_APB1RSTR
 *
 *  configuration in UART5
 *	 - Enable the UART
 *	 - Enable transmitter and receiver
 *   - Interrupt event
 *   - Baud rate (eg.9600 bit/s)
 * */

   /****Status Signal****
   *    TXE(bit 7) - Transmit data register empty
   *    TC(bit 6) - Transmission complete
   *    RXNE(bit 5) -Read data register not empty
   *    IDLE(bit 4) - IDLE line dectected
   *
   *
   *
   *
   **/
   /*****Configure Function****
    * Control register 1
    * USART enable in bit 13 (UE)
    * Word length in bit 12 (M)
    * Parity control enable in bit 10 (PCE)
    * Parity selection in bit 9 (PS) eg. if PS = 0 , data = 00110101 , parity bit is 0
    * Control register 2
    * Stop bit in bit 13:12 (STOP) eg. if STOP = 0, the size of stop bit is 1;
    * */
 /*****Error***
  * Overrun Error
  * Framing Error
  * Parity Error
  *
  * */


  /*****Configure Interrupt Event****
   * PE interrupt in bit 8 (PEIE)
   * TXE interrupt in bit 7 (TXEIE)
   * Transmission complete interrupt in bit 6 (TCIE)
   * RXNE interrupt in bit 5 (RXNEIE)
   * IDLE interrupt in bit 4 (IDLEIE)
   *
   *
   * UART5_IRQHandler();  find from startip_stm32f429
   * UART5_IRQn // define  find from stm32f429
   * HAL_NVIC_EnableIRQ(); find from stm32f4xx_hal_cortex.c
   *
   *
   * */

  /*****Configure Baud Rate****
   *  The equation of Baud rate is used in "Standard USART".
   *  When OVER8 = 0, the fractional part is coded on 4 bit and programmed by the
   *  DIV_fraction[3:0] bits in the USART_BRR register.
   *  The PCLK can be get from HAL_RCC_GetPCLK1Freq() function
   *  The SysClk can be get form  HAL_RCC_GetSysClockFreq() function
   *  SysClk = 180MHz
   *  PCLK = 45MHz
   *  
   *
   *
   *
   * */
#define noiseDetected    getUART5Status(FLAG_NF)
#define framingErr       getUART5Status(FLAG_FE)
#define parityErr        getUART5Status(FLAG_PE)
#define overRunErr       getUART5Status(FLAG_ORE)

#define NOISE_DETECTED   1
#define FRAMING_ERRPR    1
#define PARITY_ERROR     1
#define OVERRUN_ERROR    1
#define NON_ERROR        0

//-------------------INTERRUPT EVENT--------------------------//
void checkUART5err(int* noise,int* framErr,int* parErr, int* OverErr){
	 *noise = NON_ERROR;
	 *framErr = NON_ERROR;
	 *parErr = NON_ERROR;
	 *OverErr = NON_ERROR;
	if( noiseDetected ){
     *noise = NOISE_DETECTED;
	}
	if( framingErr ){
     *framErr = FRAMING_ERRPR;
	}
	if( parityErr ){
	 *parErr = PARITY_ERROR;
	}
	if( overRunErr ){
	 *OverErr = OVERRUN_ERROR;
	}
}

void handleUART5ErrInInterrupt(){
   uint32_t temReg;
	if(noiseDetected && enableEIE){
	  temReg = UART5->SR;
	  temReg = UART5->DR;
	}

	if(framingErr && enableEIE){
	  temReg = UART5->SR;
	  temReg = UART5->DR;
	}

	if(parityErr && enablePEIE){
	  temReg = UART5->SR;
	  temReg = UART5->DR;
	}

	if( (overRunErr && enableEIE) || (overRunErr && enableRXNEIE) ){
	  temReg = UART5->SR;
	  temReg = UART5->DR;
	}
}

 void handleUART5err(){
  uint32_t temReg;
 	if( noiseDetected || framingErr || parityErr || overRunErr){
     temReg = UART5->SR;
     temReg = UART5->DR;
 	}
 }

void clearInterruptFlag(){
 	UART5->SR = 0;
 }


void congifureUART_IE(UART* uartPtr, int txIE,int tcIE, int rxIE, int parityIE, int ErrIE ){

	uartPtr->CR1 |= ( parityIE << 8);
	uartPtr->CR1 |= ( txIE << 7);
	uartPtr->CR1 |= ( tcIE << 6);
	uartPtr->CR1 |= ( rxIE << 5);
	uartPtr->CR3 |= ( ErrIE << 0);
	uint32_t checkCR1 = uartPtr->CR1;
	uint32_t checkCR3 = uartPtr->CR3;
}

//----------------------UART CONFIGURATION----------------------//
void configureUART(UART* uartPtr,int baudRate, uint32_t parity, uint32_t stopBit, uint32_t wordLength){
  uart5UnresetEnableClock();
  uint32_t checkCR1;
  uint32_t checkCR2;
  uint32_t checkCR3;
  uint32_t checkBRR;
  uartPtr->CR1 |= ( OVER8_IS_1 << 15);
  uartPtr->CR1 |= ( parity << 10);
  if(parity){
   uartPtr->CR1 |= ( EVEN_PARITY << 9);
  }
  uartPtr->CR1 |= ( wordLength << 12);
  uartPtr->CR1 |= ( UART_ENABLE << 13 );
  uartPtr->CR1 |= ( UART_RECEIVER_ENABLE << 2 );
  uartPtr->CR1 |= ( UART_TRANSMITTER_ENABLE << 3 );
  uartPtr->CR2 &= ~( 3 << 12);
  uartPtr->CR2 |= ( stopBit << 12 );
  uartPtr->CR3 |= ( THREE_BIT_SAMPLE <<11 );
  uartPtr->BRR = baudRateSetting(baudRate,HAL_RCC_GetPCLK1Freq());

 //uartPtr->BRR = baudRateAlgorithm(9600,HAL_RCC_GetPCLK1Freq(),OVER8_IS_1);


 // uartPtr->BRR = 0x00002497;
  checkCR1 = uartPtr->CR1;
  checkCR2 = uartPtr->CR2;
  checkCR3 = uartPtr->CR3;
  checkBRR = uartPtr->BRR;
}

//Unable Reset and Enable Clock for UART5
void uart5UnresetEnableClock(void){
  rcc* rccPtr = RCC_BASE_ADDRESS;
  rccPtr->APB1ENR |=  1 << 20;
  rccPtr->APB1RSTR |=  0 << 20;
}

//-----------------TANSMITTION-------------//
void sendByle(uint8_t Data){
  while( !readyTransmit );
   UART5->DR = Data;
}

//-----------------RECEIVED--------------///
uint8_t receivedByle(void){
   uint32_t checkSR = UART5->SR;
   while( !readyReceived ); // if RXNE = 1, The input of data is received.
   uint32_t checkDR = UART5->DR;
   return UART5->DR;
}

//------------------TOOL---------------//
int getBit( uint32_t* reg, int posBit ){
  uint32_t store = *reg;
  return (( store >> posBit) & 1 );
}

int getUART5Status( int posBit ){
  uint32_t checkSR = UART5->SR;
  return (( UART5->SR  >> posBit) & 1 );
}

void sendBreak(void){
  UART5->CR1 |=  TRANSMIT_BREAK << 0;
}

void stopBreak(void){
	UART5->CR1 |=  NO_TRANSMIT_BREAK << 0;
}

void sendStringByInterrupt(uint8_t* Data){
	uint8_t butter;
	uint32_t checkSR = UART5->SR;
	while(*Data != NULL){
	   butter = *Data++;
	   sendByle(butter);
	}
	 UART5->SR = checkSR;
}

void getStringByInterrupt(uint8_t butter[], int* size){

}

void putData(uint8_t* Data){
   uint8_t butter;
   uint32_t checkSR = UART5->SR;
   while(*Data != NULL){
      butter = *Data++;
      sendByle(butter);
   }
   UART5->SR = checkSR;
}

void uartEnableDMA(UART* uart){
 uint32_t checkCR3;
 uart->CR3 |=  1 << DMAT_BIT ;
 uart->CR3 |=  1 << DMAR_BIT ;
 checkCR3 = uart->CR3;
}



/*
uint8_t receivedData(void){
   uint32_t checkSR = UART5->SR;
   while( !getUART5Status(RXNE) ); // if RXNE = 1, The input of data is received.
   uint32_t checkDR = UART5->DR;
   return UART5->DR;
}

void getData(uint8_t Data[]){
	uint8_t checkReCeiDAta;
  uint8_t i = 0;
  Data[i] = receivedByle() & (uint8_t)0x0ff;
  checkReCeiDAta = Data[i];
  uint32_t checkSR = UART5->SR;
  while(Data[i] != '\r'){
    i++;
    Data[i] = receivedByle() & (uint8_t)0x0ff;
    checkReCeiDAta = Data[i];
  }
    Data[i] = '\0';
}

void sendData(uint8_t* Data){
   uint32_t checkSR = UART5->SR;
   while( !getUART5Status(TXE) );
   checkSR = UART5->SR;
   UART5->DR = *Data ;  //The word length of data is 8,so Data and with 0x0ff;
}

void putData(uint8_t* Data){
   uint8_t butter;
   uint32_t checkSR = UART5->SR;
   while(*Data != NULL){
      butter = *Data++;
      sendData(butter);
   }
   UART5->SR = checkSR;
}

int haveReceivedData(){
   return getUART5Status(RXNE);
}

*/
