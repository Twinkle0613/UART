#include "UART.h"
#include "Rcc.h"
#include "BaudRateAlgorithm.h"
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
// CR2
//  00000000 00000000 00000000 00000000   
// CR1
//binary  00000000 00000000 00110001 11111100   
//Hex       00         00       31      FC




configureUART(UART* uartPtr){
	//UART *uartPtr = UART5_BASE_ADDRESS;
  uartPtr->CR1 = 0x000031FC;
  uartPtr->CR2 = 0x00000000;
  baudRateSetting(115200,HAL_RCC_GetPCLK1Freq(),uartPtr->BRR); 
}


uartUnresetEnableClock(void){
  rcc* rccPtr = RCC_BASE_ADDRESS;
  rccPtr->APB1ENR &= ~( 1 << 20 );
  rccPtr->APB1ENR |=  1 << 20;

  rccPtr->APB1RSTR &= ~( 1 << 20 );
  rccPtr->APB1RSTR |=  0 << 20;
}


/*

	uartPtr->CR1 &= ~( 1 << 13 );
	uartPtr->CR1 |=  1 << 13;
  //Word length (M) in bit 12
	uartPtr->CR1 &= ~( 1 << 12 );
	uartPtr->CR1 |=  1 << 12;
  //Parity control enable (PCE) in bit 10
	uartPtr->CR1 &= ~( 1 << 10 );
    uartPtr->CR1 |=  1 << 10;
  //Parity selection (PS) in bit 9
  //  eg. if PS = 0 , data = 00110101 , parity bit is 0
    uartPtr->CR1 &= ~( 1 << 9 );
    uartPtr->CR1 |=  0 << 9;
    
            //   0X08000000
            */

