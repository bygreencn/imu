#include "pressure.h"

char read_i2c_reg(I2C_TypeDef * I2Cx, char addr, char reg_number, char * value)
{
	volatile uint32_t timeout = I2C_TIMEOUT;
	while(I2C_CheckEvent(I2Cx, I2C_FLAG_BUSY))
		if(timeout-- == 0)
			return -1;
	I2C_GenerateSTART(I2Cx, ENABLE);
	timeout = I2C_TIMEOUT;
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
		if(timeout-- == 0)
			return -2;
	I2C_Send7bitAddress(I2Cx, addr & 0xFE, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT;
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		if(timeout-- == 0)
			return -3;
	I2C_SendData(I2Cx, reg_number);
	timeout = I2C_TIMEOUT;
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF) == RESET)
		if(timeout-- == 0)
			return -4;
	I2C_GenerateSTART(I2Cx, ENABLE);
	timeout = I2C_TIMEOUT;
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
		if(timeout-- == 0)
			return -5;
	I2C_Send7bitAddress(I2Cx, addr & 0xFE, I2C_Direction_Receiver);
	timeout = I2C_TIMEOUT;
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR) == RESET)
		if(timeout-- == 0)
			return -6;
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	(void)I2Cx->SR2;
	I2C_GenerateSTOP(I2Cx, ENABLE);
	timeout = I2C_TIMEOUT;
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_RXNE) == RESET)
		if(timeout-- == 0)
			return -7;
	*value = I2C_ReceiveData(I2Cx);
	timeout = I2C_TIMEOUT;
	while(I2Cx->CR1 & I2C_CR1_STOP)
		if(timeout-- == 0)
			return -8;
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	return 0;
}

char write_i2c_reg(I2C_TypeDef * I2Cx, char addr, char reg_number, char value)
{
	return 0;
}

