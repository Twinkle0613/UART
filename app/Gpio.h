#ifndef __Gpio_H__
#define __Gpio_H__
//#include "Rcc.h"
#include <stdint.h>
#include "stm32f4xx_hal_gpio.h"
#define GPIO_OUTPUT GPIO_MODE_OUTPUT_PP
#define GPIO_INPUT GPIO_MODE_INPUT

typedef struct GPIO_t GPIO;
struct GPIO_t{
 uint32_t MODER;
 uint32_t OTYPER;
 uint32_t OSPEED;
 uint32_t PUPDR;
 uint32_t IDR;
 uint32_t ODR;
 uint32_t BSRR;
 uint32_t LCKR;
 uint32_t AFRL;
 uint32_t AFRH;
};

#define RCC_BASE_ADDRESS 0x40023800

#define PIN_0					0
#define PIN_1					1
#define PIN_2   		        2
#define PIN_3   		        3
#define PIN_4   		        4
#define PIN_5   		        5
#define PIN_6					6
#define PIN_7   		        7
#define PIN_8   		        8
#define PIN_9 	 		        9
#define PIN_10   		        10
#define PIN_11					11
#define PIN_12   		        12
#define PIN_13   		        13
#define PIN_14   		        14
#define PIN_15   		        15

#define GPIO_MODE_INPUT 	     0
#define GPIO_MODE_OUTPUT	     1
#define GPIO_MODE_ALFUNCTION     2
#define GPIO_MODE_ANALOG   		 3


#define OUTPUT_PUSH_PULL		0
#define OUTPUT_OPEN_DRAIN       1


#define LOW_SPEED  				0
#define MEDIUM_SPEED        	1
#define HIGH_SPEED				2
#define VERY_HIGH_SPEED    		3

#define GPIOA_BASE_ADDRESS 0x40020000
#define GPIOB_BASE_ADDRESS 0x40020400
#define GPIOC_BASE_ADDRESS 0x40020800
#define GPIOD_BASE_ADDRESS 0x40020C00
#define GPIOG_BASE_ADDRESS 0x40021800

#define PORTA	((GPIO *)GPIOA_BASE_ADDRESS)
#define PORTB	((GPIO *)GPIOB_BASE_ADDRESS)
#define PORTC	((GPIO *)GPIOC_BASE_ADDRESS)
#define PORTD	((GPIO *)GPIOD_BASE_ADDRESS)
#define PORTG	((GPIO *)GPIOG_BASE_ADDRESS)
configureIntPin(int direction,int pinNum, GPIO* port);
configureOutPin(int direction, int pinNum, GPIO *port);
configureAlterFuncPin(int pinNum, GPIO *port, int valueAFR);
void writeOne(int pinNum, GPIO_TypeDef *port);
void writeZero(int pinNum, GPIO_TypeDef *port);


#define NO_PULL_UD	0
#define PULL_UP 	1
#define PULL_DOWN 	2



#endif //__Gpio_H__
