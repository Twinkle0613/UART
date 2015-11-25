#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>
typedef struct UART_t UART;

struct UART_t{
 uint32_t SR;
 uint32_t DR;
 uint32_t BRR;
 uint32_t CR1;
 uint32_t CR2;
 uint32_t CR3;
 uint32_t GTPR;
};
configureUART(UART* uartPtr);
uartUnresetEnableClock(void);
void getData(uint8_t* Data);
void putData( uint8_t* Data);
void sendData(uint8_t Data);
uint8_t receivedData(void);
#define UART5_BASE_ADDRESS 0x40005000
#define UART4_BASE_ADDRESS 0x40004fff
#define UART5	((UART *)UART5_BASE_ADDRESS)

#endif //__UART_H__
