#define USE_STDPERIPH_DRIVER
#define STM32F10X_HD
#include "stm32f10x.h"
#include <stdio.h>

#define BAUD_RATE 9600

int main(void);
void hw_init(void);
int __io_putchar(int ch);

int main()
{
	hw_init();
	while(1);
	return 0;
}

void hw_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;

	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB | RCC_APB1Periph_USART2 | RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); 

	//Configuring the Alternative Function Push-Pull pins
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	// GPIOA: RTS, TX, (CS), SCK, MOSI => PA1, PA2, PA5, PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// GPIOC: D0-D3, SD_CLK => PC8, PC9, PC10, PC11, PC12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// GPIOD: SD_CMD => PD2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//Configuring the Alternate Function Open Drain pins
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	// GPIOB: SCL1, SDA1, SCL2, SDA2 => PB6, PB7, PB10, PB11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Configuring the General Purpose Push-Pull pins
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	// GPIOA: USB_DISCONNECT => PA10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// GPIOB: RP_ST, RP_SPD, RP_HP, LED, Y_ST, Y_SPD => PB1, PB2, PB5, PB9, PB14, PB15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_9 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Configuring the Analog Input pins
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	// GPIOC: X, Y, RefXY, Z, RefZ => PC0, PC1, PC2, PC4, PC5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//Configuring the Floating Inputs pins
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	// GPIOA: CTS, RX, MISO, INT1_PS => PA0, PA3, PA6, PA9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// GPIOB: DRDY_M, INT1_ACC, INT2_ACC => PB8, PB12, PB13
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// GPIOC: OV/INT_TMP, TAMPER => PC6, PC13
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//EXTI_ClearITPendingBit(EXTI_Line18);
	//EXTI_InitStructure.EXTI_Line = EXTI_Line18;
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	//EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	//EXTI_Init(&EXTI_InitStructure);

	USART_InitStructure.USART_BaudRate = BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);

	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_Init(&I2C_InitStructure, I2C1); //For Accelerometer & magnetometer
	I2C_Init(&I2C_InitStructure, I2C2); //For Temperature & Pressure sensor

	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//NVIC_InitStructure.MVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);

	//NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	//NVIC_Init(&NVIC_InitStructure);
}

int __io_putchar(int ch)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	USART_SendData(USART2, (uint8_t) ch);
	return ch;
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1);
}

#endif
