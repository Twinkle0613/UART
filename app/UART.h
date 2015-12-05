#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>
typedef struct UART_t UART;


#define readyTransmit getUART5Status(FLAG_TXE)
#define readyReceived getUART5Status(FLAG_RXNE)

struct UART_t{
 uint32_t SR;
 uint32_t DR;
 uint32_t BRR;
 uint32_t CR1;
 uint32_t CR2;
 uint32_t CR3;
 uint32_t GTPR;
};
void clearInterruptFlag();
int getUART5Status( int posBit );
void congifureUART_IE(UART* uartPtr, int txIE,int tcIE, int rxIE, int parityIE, int ErrIE );
void configureUART(UART* uartPtr,int baudRate, uint32_t parity, uint32_t stopBit, uint32_t wordLength);
void uart5UnresetEnableClock(void);
void sendByle(uint8_t Data);
uint8_t receivedByle();
int getUART5Status( int posBit );

/*
void getData(uint8_t* Data);
void putData( uint8_t* Data);
void sendData(uint8_t* Data);
uint8_t receivedData(void);
*/
//**STATUS SIGNAL**
/*
typedef enum{
 NON_ERROR,
 NOISE_DETECTED,
 PARITY_ERROR,
 FRAMING_ERRPR,
 OVERRUN_ERROR,
}uartErr;
*/


#define _readyReceived getUART5Status(RXNE)

#define FLAG_CTS 9
#define FLAG_LBD 8
#define FLAG_TXE 7
#define FLAG_TC 6
#define FLAG_RXNE 5
#define FLAG_IDLE 4
#define FLAG_ORE 3
#define FLAG_NF 2
#define FLAG_FE 1
#define FLAG_PE 0



#define UART5_BASE_ADDRESS 0x40005000
#define UART4_BASE_ADDRESS 0x40004fff
#define UART5	((UART *)UART5_BASE_ADDRESS)
#define UART4   ((UART *)UART4_BASE_ADDRESS)

#define UART_WORDLENGTH_8B 0
#define UART_WORDLENGTH_9B 1

#define UART_STOPBITS_1 0
#define UART_STOPBITS_2 2

#define UART_PARITY_ENABLE 1
#define UART_PARITY_DISABLE 0

#define EVEN_PARITY 0
#define ODD_PARITY 1

#define THREE_BIT_SAMPLE 0
#define ONE_BIT_SAMPLE 1

#define UART_ENABLE 1
#define UART_DISABLE 0

#define UART_RECEIVER_ENABLE 1
#define UART_RECEIVER_DISABLE 0

#define UART_TRANSMITTER_ENABLE 1
#define UART_TRANSMITTER_DISABLE 0
//EIE
#define ERROR_IE 1
#define ERROR_ID 0
//PEIE
#define PARITY_IE 1
#define PARITY_ID 0
//TXEIE
#define TX_EMPTY_IE 1
#define TX_EMPTY_ID 0
//TCEIE
#define TX_COMPLETE_IE 1
#define TX_COMPLETE_ID 0
//RXNEIE
#define RX_NOT_EMPTY_IE 1
#define RX_NOT_EMPTY_ID 0
//IDLEIE
#define IDLE_IE 1
#define IDLE_ID 0



#endif //__UART_H__
