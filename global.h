#ifndef __GLOBAL_DEFS__
#define __GLOBAL_DEFS__

#define USE_STDPERIPH_DRIVER
#define STM32F10X_HD
#include "stm32f10x.h"
#include <stdio.h>

#include "pressure.h"

//USART parameters
#define BAUD_RATE 9600

//I2C parameters
#define I2C_TIMEOUT 0x1000
#define ADDR_PRESS 0xBA
#define ADDR_TEMP 0x90
#define ADDR_ACC 0x32
#define ADDR_MAG 0x3C
#define I2C_PRESS I2C2
#define I2C_TEMP I2C2
#define I2C_ACC I2C1
#define I2C_MAG I2C1

//LED control defines
#define LED_ON() GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LED_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#endif
