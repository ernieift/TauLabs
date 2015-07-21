#
# Rules to add CMSIS4 DSP Library to a target
#

CMSIS4_DSPLIB_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifeq ($(INCLUDE_ALL_DSP),YES)
SRC += $(wildcard $(CMSIS4_DSPLIB_DIR)Source/*/*.c)
else
SRC += $(CMSIS4_DSPLIB_DIR)/Source/TransformFunctions/arm_cfft_radix4_init_q15.c
SRC += $(CMSIS4_DSPLIB_DIR)/Source/TransformFunctions/arm_cfft_radix4_q15.c
SRC += $(CMSIS4_DSPLIB_DIR)/Source/BasicMathFunctions/arm_shift_q15.c
SRC += $(CMSIS4_DSPLIB_DIR)/Source/ComplexMathFunctions/arm_cmplx_mag_q15.c
SRC += $(CMSIS4_DSPLIB_DIR)/Source/FastMathFunctions/arm_sqrt_q15.c
SRC += $(CMSIS4_DSPLIB_DIR)/Source/CommonTables/arm_common_tables.c
SRC += $(CMSIS4_DSPLIB_DIR)/Source/TransformFunctions/arm_bitreversal.c
endif

EXTRAINCDIRS += $(CMSIS4_DSPLIB_DIR)/../Include

