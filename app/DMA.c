#include "DMA.h"
#include "Rcc.h"
/**
 *  The UART5 RX is in the Channel 4 of Stream 0;
 *  The UART5 TX is in the Channel 4 of Stream 7;
 *  Configure Register
 *  DMA_SxCR
 *        27-25 CHSEL[2:0]: 000(Chanel0) and 111(Chanel7)
 *        19 CT: 0
 *        14-13 MSIZE[1:0]: 00 (8-byte)
 *        12-11 PSIZE[1:0]: 00 (8-byte)
 *        10 MINC: 1 (increment)
 *        7-6 DIR[1:0]: 00(peripheral-to-memory)/01(memory-to-peripheral)
 *        4 TCIE: 1 (Enable)
 *        5 HTIE: 1 (Enable)
 *        2 TEIE: 1 (Enable)
 *        1 DMEIE: 1 (Enable)
 *        0 EN: 1(On)/0(Off)
 * |================================================================================|
 * |                stream0              |              stream7                     |
 * |=====================================|==========================================|
 * |         DMA_LISR(Status)            |              DMA_HISR                    |
 * |	5       4      3      2      0   |     27      26       25     24     22    |
 * |  TCIF0  HTIF0  TEIF0  DMEIF0 FEIF0  |    TCIF7   HTIF7   TEIF7  DMEIF7  FEIF7  |
 * |-------------------------------------|------------------------------------------|
 * |         DMA_LIFCR(CLear)            |              DMA_HIFCR(Clear)            |
 * |   5     4      3        2      0    |    27     26       25       24      22   |
 * |CTCIF0 HTIF0  CTEIF0  CDMEIF0 CFEIF0 | CTCIF7  CHTIF7   CTEIF7  CDMEIF7  CFEIF7 |
 * |-------------------------------------|------------------------------------------|
 * |       Peripheral-to-memory          |           Memory-to-peripheral           |
 * | Source Address   Destination Address|   Source Address   Destination Address   |
 * |    DMA_SxPAR         DMA_SxM0AR     |     DMA_SxM0AR         DMA_SxPAR         |
 * |                                     |											|
 * |-------------------------------------|------------------------------------------|
 */



/*
 *        27-25 CHSEL[2:0]: 000(Chanel0) and 111(Chanel7)
 *        19 CT: 0
 *        14-13 MSIZE[1:0]: 00 (8-byte)
 *        12-11 PSIZE[1:0]: 00 (8-byte)
 *        10 MINC: 1 (increment)
 *        7-6 DIR[1:0]: 00(peripheral-to-memory)/01(memory-to-peripheral)
 *        4 TCIE: 1 (Enable)
 *        3 HTIE: 1 (Enable)
 *        2 TEIE: 1 (Enable)
 *        1 DMEIE: 1 (Enable)
 *        0 EN: 1(On)/0(Off)
 */
void configureDMA(DMA *dma,
		          int st,
		          int channel,
		          int transDireation,
		          int priSize,
		          int memorySize,
		          uint32_t source,
		          uint32_t destination,
		          uint32_t dataSize){
	dmaUnresetEnableClock(dma);
	stream *s = &dma->S0;
	stream *ptr = &s[st];
	ptr->CR = 0;
	ptr->CR &= ~(7 << 25);
	ptr->CR |= channel << 25;
	ptr->CR |= CT_MEMORY0 << 19;
	ptr->CR &= ~( 3 << 13 );
	ptr->CR |= memorySize << 13;
	ptr->CR &= ~( 3 << 11 );
	ptr->CR |= priSize << 11;
	ptr->CR |= INCREMENT << 10;
	ptr->CR &= ~( 3 << 6 );
	ptr->CR |= transDireation << 6;
	ptr->CR |= TC_IE << 4;
	ptr->CR |= HT_ID << 3;
	ptr->CR |= TE_ID << 2;
	ptr->CR |= DME_ID << 1;

	ptr->NDTR = (uint32_t)dataSize;
	if(transDireation == PERIPHERAL_TO_MEMORY){
		ptr->PAR = (uint32_t)source;
		ptr->M0AR = (uint32_t)destination;
	}else if(transDireation == MEMORY_TO_PERIPHERAL){
		ptr->PAR = (uint32_t)destination;
		ptr->M0AR = (uint32_t)source;
	}else if( transDireation == MEMORT_TO_MEMORY){
		ptr->PAR = (uint32_t)source;
		ptr->M0AR = (uint32_t)destination;
	}
}



void dmaUnresetEnableClock(DMA* dma){
	rcc* rccPtr = RCC_BASE_ADDRESS;
	if( dma == DMA1_BASE_ADDRESS){
	  rccPtr->AHB1ENR |=  1 << 21;
	  rccPtr->AHB1RSTR |=  0 << 21;
	}else if( dma == DMA2_BASE_ADDRESS ){
	  rccPtr->AHB1ENR |=  1 << 22;
	  rccPtr->AHB1RSTR |=  0 << 22;
	}
}
void enableDmaTX(DMA* dma){
  dma->S7.CR |= 1;
}

void enableDmaRX(DMA* dma){
	dma->S0.CR |= 1;
}

int getDMA2Status( int st,int posBit ){
 uint32_t checkLISR = DMA2->LISR;
 uint32_t checkHISR = DMA2->HISR;
 if(st < 4)
  return (( DMA2->LISR >> posBit) & 1 );
 else
  return (( DMA2->HISR >> posBit) & 1 );
}

int getDMA1Status( int st,int posBit ){
 uint32_t checkLISR = DMA1->LISR;
 uint32_t checkHISR = DMA1->HISR;
 if(st < 4)
  return (( DMA1->LISR >> posBit) & 1 );
 else
  return (( DMA1->HISR >> posBit) & 1 );
}

void clearDMAFlag(DMA* dma,int st,int posBit){
   uint32_t checkLIFCR;
   uint32_t checkHIFCR;

  if(st < 4)
	  dma->LIFCR |= ( 1 << posBit );
  else
	  dma->HIFCR |= ( 1 << posBit );

  checkHIFCR= dma->HIFCR;
  checkLIFCR = dma->LIFCR;
  uint32_t checkLISR = DMA1->LISR;
  uint32_t checkHISR = DMA1->HISR;
}

void clearDMAstatus(DMA* dma,int st){
	if(st < 4)
		DMA1->LIFCR =  (uint32_t)1 ;
	else
		DMA1->HIFCR =  (uint32_t)1 ;
}
