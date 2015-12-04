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
void configureUART(UART* uartPtr,int baudRate, uint32_t parity, uint32_t stopBit, uint32_t wordLength);
void uart5UnresetEnableClock(void);
void sendByle(uint8_t Data);
uint8_t receivedByle();
int readyReceived();
int readySend();
int getUART5Status( int posBit );

/*
void getData(uint8_t* Data);
void putData( uint8_t* Data);
void sendData(uint8_t* Data);
uint8_t receivedData(void);
*/
//**STATUS SIGNAL**
#define CTS 9
#define LBD 8
#define TXE 7
#define TC 6
#define RXNE 5
#define IDLE 4
#define ORE 3
#define NF 2
#define FE 1
#define PE 0



#define UART5_BASE_ADDRESS 0x40005000
#define UART4_BASE_ADDRESS 0x40004fff
#define UART5	((UART *)UART5_BASE_ADDRESS)
#define UART4   ((UART *)UART4_BASE_ADDRESS)

#define UART_WORDLENGTH_8B ((uint32_t)0x00000000)
#define UART_WORDLENGTH_9B ((uint32_t)0x00000001)

#define UART_STOPBITS_1 ((uint32_t)0x00000000)
#define UART_STOPBITS_2 ((uint32_t)0x00000010)

#define UART_PARITY_ENABLE ((uint32_t)0x00000001)
#define UART_PARITY_DISABLE ((uint32_t)0x0000000)

#define UART_ENABLE ((uint32_t)0x00000001)
#define UART_DISABLE ((uint32_t)0x00000000)

#define UART_RECEIVER_ENABLE ((uint32_t)0x00000001)
#define UART_RECEIVER_DISABLE ((uint32_t)0x00000000)

#define UART_TRANSMITTER_ENABLE ((uint32_t)0x00000001)
#define UART_TRANSMITTER_DISABLE ((uint32_t)0x00000000)

#endif //__UART_H__
