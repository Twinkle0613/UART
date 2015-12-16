#ifndef __DMA_H__
#define __DMA_H__
#include <stdint.h>
typedef struct stream_t stream;
typedef struct dma_t DMA;
struct stream_t{
	uint32_t CR;
	uint32_t NDTR;
	uint32_t PAR;
	uint32_t M0AR;
	uint32_t M1AR;
	uint32_t FCR;
};

struct dma_t{
	uint32_t LISR;
	uint32_t HISR;
	uint32_t LIFCR;
	uint32_t HIFCR;
	stream S0;
	stream S1;
	stream S2;
	stream S3;
	stream S4;
	stream S5;
	stream S6;
	stream S7;
};



void configureDMA(DMA *dma,
		          int st,
		          int channel,
		          int transDireation,
		          int priSize,
		          int memorySize,
		          uint32_t source,
		          uint32_t destination,
                  uint32_t dataSize);

void dmaUnresetEnableClock(DMA* dma);
void enableDmaRX(DMA* dma);
void enableDmaTX(DMA* dma);
void clearDMAFlag(DMA* dma,int st,int posBit);
void clearDMAstatus(DMA* dma,int st);
int getDMA1Status( int st,int posBit );
int getDMA2Status( int st,int posBit );
#define DMA1_BASE_ADDRESS 0x40026000
#define DMA2_BASE_ADDRESS 0x40026400

#define DMA1 ((DMA *)DMA1_BASE_ADDRESS)
#define DMA2 ((DMA *)DMA2_BASE_ADDRESS)

#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4
#define CHANNEL5 5
#define CHANNEL6 6
#define CHANNEL7 7
#define CHANNEL8 8

#define STREAM0 0
#define STREAM1 1
#define STREAM2 2
#define STREAM3 3
#define STREAM4 4
#define STREAM5 5
#define STREAM6 6
#define STREAM7 7

#define CT_MEMORY0 0
#define CT_MEMORY1 1

#define BYTE 0
#define HALF_WORD 1
#define WORD 2

#define FIXED 0
#define INCREMENT 1

#define PERIPHERAL_TO_MEMORY 0
#define MEMORY_TO_PERIPHERAL 1
#define MEMORT_TO_MEMORY 2

#define TC_ID 0
#define TC_IE 1

#define HT_ID 0
#define HT_IE 1

#define TE_ID 0
#define TE_IE 1

#define DME_ID 0
#define DME_IE 1

#define DIS 0
#define ENA 1

#define FLAG_TCIF7   27
#define FLAG_HTIF7   26
#define FLAG_TEIF7   25
#define FLAG_DMEIF7  24
#define FLAG_FEIF7   22

#define FLAG_TCIF0   5
#define FLAG_HTIF0   4
#define FLAG_TEIF0   3
#define FLAG_DMEIF0  2
#define FLAG_FEIF0   0


#define compTransmitTX getDMA1Status(STREAM7,FLAG_TCIF7)
#define compReceiveRX getDMA1Status(STREAM0,FLAG_TCIF0)
#endif //__DMA_H__
