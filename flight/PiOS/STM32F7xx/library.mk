#
# Rules to (help) build the F7xx device support.
#

#
# Compiler options implied by the F7xx
#
CDEFS				+= -DSTM32F7
CDEFS				+= -DSTM32F7XX
CDEFS				+= -DSTM32F746xx
CDEFS				+= -DHSE_VALUE=$(OSCILLATOR_FREQ)
CDEFS 				+= -DUSE_HAL_DRIVER
ARCHFLAGS			+= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard

#
# PIOS device library source and includes
#
EXTRAINCDIRS		+=	$(PIOS_DEVLIB)/inc

#
# CMSIS for the F7
#
include $(PIOSCOMMONLIB)/CMSIS4/library.mk
CMSIS4_DEVICEDIR	:=	$(PIOS_DEVLIB)/Libraries/CMSIS4/Device/ST/STM32F7xx
SRC			+=	$(BOARD_INFO_DIR)/cmsis_system.c
EXTRAINCDIRS		+=	$(CMSIS4_DEVICEDIR)/Include

#
# HAL library
#
PERIPHLIB			 =	$(PIOS_DEVLIB)/Libraries/STM32F7xx_HAL_Driver
EXTRAINCDIRS		+=	$(PERIPHLIB)/inc
SRC					+=	$(wildcard $(PERIPHLIB)/src/*.c)

#
# ST USB OTG library
#
#USBOTGLIB			=	$(PIOS_DEVLIB)/Libraries/STM32_USB_OTG_Driver
#USBOTGLIB_SRC			=	usb_core.c usb_dcd.c usb_dcd_int.c
#EXTRAINCDIRS			+=	$(USBOTGLIB)/inc
#SRC				+=	$(addprefix $(USBOTGLIB)/src/,$(USBOTGLIB_SRC))

#
# ST USB Device library
#
#USBDEVLIB			=	$(PIOS_DEVLIB)/Libraries/STM32_USB_Device_Library
#EXTRAINCDIRS			+=	$(USBDEVLIB)/Core/inc
#SRC				+=	$(wildcard $(USBDEVLIB)/Core/src/*.c)

#
# FreeRTOS
#
# If the application has included the generic FreeRTOS support, then add in
# the device-specific pieces of the code.
#
ifneq ($(FREERTOS_DIR),)
FREERTOS_PORTDIR	:=	$(FREERTOS_DIR)/portable
EXTRAINCDIRS		+=	$(FREERTOS_PORTDIR)/GCC/ARM_CM7/r0p1
SRC					+=	$(wildcard $(FREERTOS_PORTDIR)/GCC/ARM_CM7/r0p1/*.c)
endif
