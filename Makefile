TOOLS_PATH = ~/CodeSourcery/bin/
CROSS_COMPILE = $(TOOLS_PATH)arm-none-eabi-
CC = gcc
LD = ld
CFLAGS = -march=armv7-m -mtune=cortex-m3 -mthumb -msoft-float -mfloat-abi=soft -fno-common
LDFLAGS = 
STM32F10X_INC = stm32f10x_adc.h stm32f10x_bkp.h stm32f10x_can.h stm32f10x_crc.h stm32f10x_dac.h stm32f10x_dbgmcu.h stm32f10x_dma.h stm32f10x_exti.h stm32f10x_flash.h \
                stm32f10x_fsmc.h stm32f10x_gpio.h stm32f10x_i2c.h stm32f10x_iwdg.h stm32f10x_pwr.h stm32f10x_rcc.h stm32f10x_rtc.h stm32f10x_sdio.h stm32f10x_spi.h   \
                stm32f10x_tim.h stm32f10x_usart.h stm32f10x_wwdg.h misc.h core_cm3.h system_stm32f10x.h
STM32F10X_SRC = $(STM32F10X_INC:.h=.c)
STM32F10X_OBJ = $(STM32F10X_INC:.h=.o)

all : imu

imu : main.o startup_stm32f10x_hd.o $(STM32F10X_OBJ)
	$(CROSS_COMPILE)$(LD) -T stm32f10x_hd.ld $(LDFLAGS) $^ -o $@

main.o : main.c stm32f10x.h
	$(CROSS_COMPILE)$(CC) -c $(CFLAGS) $< -o $@

stm32f10x.h : core_cm3.h system_stm32f10x.h stm32f10x_conf.h 

stm32f10x_conf.h : $(STM32F10X_INC)

$(STM32F10X_OBJ) : %.o : %.c stm32f10x.h
	$(CROSS_COMPILE)$(CC) -c $(CFLAGS) $< -o $@

startup_stm32f10x_hd.o : startup_stm32f10x_hd.s
	$(CROSS_COMPILE)$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -rf *.o imu
