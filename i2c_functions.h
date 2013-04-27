#ifndef __I2C_FUNC__
#define __I2C_FUNC__

#include "global.h"

char read_i2c_reg(I2C_TypeDef * I2Cx, char addr, char reg_number, char * value);
char write_i2c_reg(I2C_TypeDef * I2Cx, char addr, char reg_number, char value);

#endif
