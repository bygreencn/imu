#define USE_STDPERIPH_DRIVER
#define STM32F10X_HD
#include "stm32f10x.h"


int main()
{
	return 0;
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1);
}

#endif
