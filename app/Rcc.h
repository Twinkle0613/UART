#ifndef __Rcc_H__
#define __Rcc_H__

//Reset_and_Clock_Control
#include <stdint.h>
#include "Gpio.h"
#include "stm32f4xx_hal_gpio.h"



void gpioUnresetEnableClock(GPIO *port);

typedef struct RCC_t rcc;
struct RCC_t{
 uint32_t CR;
 uint32_t PLLCFGR;
 uint32_t CFGR;
 uint32_t CIR;
 uint32_t AHB1RSTR;
 uint32_t AHB2RSTR;
 uint32_t AHB3RSTR;
 uint32_t Reserved0x1C;
 uint32_t APB1RSTR;
 uint32_t APB2RSTR;
 uint32_t Reserved0x20;
 uint32_t Reserved0x2C;
 uint32_t AHB1ENR;
 uint32_t AHB2ENR;
 uint32_t AHB3ENR;
 uint32_t Reserved0x3C;
 uint32_t APB1ENR;
 uint32_t APB2ENR;
 uint32_t Reserved0x48;
 uint32_t Reserved0x4C;
 uint32_t AHB1LPENR;
 uint32_t AHB2LPENR;
 uint32_t AHB3LPENR;
 uint32_t Reserved0x5C;
 uint32_t APB1LPENR;
 uint32_t APB2LPENR;
 uint32_t Reserved0x68;
 uint32_t Reserved0x6C;
 uint32_t BDCR;
 uint32_t CSR;
 uint32_t Reserved0x78;
 uint32_t Reserved0x7C;
 uint32_t SSCGR;
 uint32_t PLLI2SCFGR;
};

#define RCC_BASE_ADDRESS 0x40023800
#define RCC_reg	((rcc*)RCC_BASE_ADDRESS)

#define GPIOA_BIT 0
#define GPIOB_BIT 1
#define GPIOC_BIT 2
#define GPIOD_BIT 3
#define GPIOE_BIT 4
#define GPIOF_BIT 5
#define GPIOG_BIT 6
#define GPIOH_BIT 7
#define GPIOI_BIT 8


#endif //__Rcc_H__
