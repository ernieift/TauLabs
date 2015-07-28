/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 *
 * @file       vector_stm32f7xx.c
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2015
 * @brief      C based vectors for F7
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/** interrupt handler */
typedef const void	(vector)(void);

/** default interrupt handler */
static void
default_io_handler(void)
{
	for (;;) ;
}

/** prototypes an interrupt handler */
#define HANDLER(_name)	extern vector _name __attribute__((weak, alias("default_io_handler")))

HANDLER(WWDG_IRQHandler);                 // Window WatchDog
HANDLER(PVD_IRQHandler);                  // PVD through EXTI Line detection
HANDLER(TAMP_STAMP_IRQHandler);           // Tamper and TimeStamps through the EXTI line
HANDLER(RTC_WKUP_IRQHandler);             // RTC Wakeup through the EXTI line
HANDLER(FLASH_IRQHandler);                // FLASH
HANDLER(RCC_IRQHandler);                  // RCC
HANDLER(EXTI0_IRQHandler);                // EXTI Line0
HANDLER(EXTI1_IRQHandler);                // EXTI Line1
HANDLER(EXTI2_IRQHandler);                // EXTI Line2
HANDLER(EXTI3_IRQHandler);                // EXTI Line3
HANDLER(EXTI4_IRQHandler);                // EXTI Line4
HANDLER(DMA1_Stream0_IRQHandler);         // DMA1 Stream 0
HANDLER(DMA1_Stream1_IRQHandler);         // DMA1 Stream 1
HANDLER(DMA1_Stream2_IRQHandler);         // DMA1 Stream 2
HANDLER(DMA1_Stream3_IRQHandler);         // DMA1 Stream 3
HANDLER(DMA1_Stream4_IRQHandler);         // DMA1 Stream 4
HANDLER(DMA1_Stream5_IRQHandler);         // DMA1 Stream 5
HANDLER(DMA1_Stream6_IRQHandler);         // DMA1 Stream 6
HANDLER(ADC_IRQHandler);                  // ADC1, ADC2 and ADC3s
HANDLER(CAN1_TX_IRQHandler);              // CAN1 TX
HANDLER(CAN1_RX0_IRQHandler);             // CAN1 RX0
HANDLER(CAN1_RX1_IRQHandler);             // CAN1 RX1
HANDLER(CAN1_SCE_IRQHandler);             // CAN1 SCE
HANDLER(EXTI9_5_IRQHandler);              // External Line[9:5]s
HANDLER(TIM1_BRK_TIM9_IRQHandler);        // TIM1 Break and TIM9
HANDLER(TIM1_UP_TIM10_IRQHandler);        // TIM1 Update and TIM10
HANDLER(TIM1_TRG_COM_TIM11_IRQHandler);   // TIM1 Trigger and Commutation and TIM11
HANDLER(TIM1_CC_IRQHandler);              // TIM1 Capture Compare
HANDLER(TIM2_IRQHandler);                 // TIM2
HANDLER(TIM3_IRQHandler);                 // TIM3
HANDLER(TIM4_IRQHandler);                 // TIM4
HANDLER(I2C1_EV_IRQHandler);              // I2C1 Event
HANDLER(I2C1_ER_IRQHandler);              // I2C1 Error
HANDLER(I2C2_EV_IRQHandler);              // I2C2 Event
HANDLER(I2C2_ER_IRQHandler);              // I2C2 Error
HANDLER(SPI1_IRQHandler);                 // SPI1
HANDLER(SPI2_IRQHandler);                 // SPI2
HANDLER(USART1_IRQHandler);               // USART1
HANDLER(USART2_IRQHandler);               // USART2
HANDLER(USART3_IRQHandler);               // USART3
HANDLER(EXTI15_10_IRQHandler);            // External Line[15:10]s
HANDLER(RTC_Alarm_IRQHandler);            // RTC Alarm (A and B) through EXTI Line
HANDLER(OTG_FS_WKUP_IRQHandler);          // USB OTG FS Wakeup through EXTI line
HANDLER(TIM8_BRK_TIM12_IRQHandler);       // TIM8 Break and TIM12
HANDLER(TIM8_UP_TIM13_IRQHandler);        // TIM8 Update and TIM13
HANDLER(TIM8_TRG_COM_TIM14_IRQHandler);   // TIM8 Trigger and Commutation and TIM14
HANDLER(TIM8_CC_IRQHandler);              // TIM8 Capture Compare
HANDLER(DMA1_Stream7_IRQHandler);         // DMA1 Stream7
HANDLER(FSMC_IRQHandler);                 // FSMC
HANDLER(SDMMC1_IRQHandler);               // SDMMC1
HANDLER(TIM5_IRQHandler);                 // TIM5
HANDLER(SPI3_IRQHandler);                 // SPI3
HANDLER(USART4_IRQHandler);               // UART4
HANDLER(USART5_IRQHandler);               // UART5
HANDLER(TIM6_DAC_IRQHandler);             // TIM6 and DAC1&2 underrun errors
HANDLER(TIM7_IRQHandler);                 // TIM7
HANDLER(DMA2_Stream0_IRQHandler);         // DMA2 Stream 0
HANDLER(DMA2_Stream1_IRQHandler);         // DMA2 Stream 1
HANDLER(DMA2_Stream2_IRQHandler);         // DMA2 Stream 2
HANDLER(DMA2_Stream3_IRQHandler);         // DMA2 Stream 3
HANDLER(DMA2_Stream4_IRQHandler);         // DMA2 Stream 4
HANDLER(ETH_IRQHandler);                  // Ethernet
HANDLER(ETH_WKUP_IRQHandler);             // Ethernet Wakeup through EXTI line
HANDLER(CAN2_TX_IRQHandler);              // CAN2 TX
HANDLER(CAN2_RX0_IRQHandler);             // CAN2 RX0
HANDLER(CAN2_RX1_IRQHandler);             // CAN2 RX1
HANDLER(CAN2_SCE_IRQHandler);             // CAN2 SCE
HANDLER(OTG_FS_IRQHandler);               // USB OTG FS
HANDLER(DMA2_Stream5_IRQHandler);         // DMA2 Stream 5
HANDLER(DMA2_Stream6_IRQHandler);         // DMA2 Stream 6
HANDLER(DMA2_Stream7_IRQHandler);         // DMA2 Stream 7
HANDLER(USART6_IRQHandler);               // USART6
HANDLER(I2C3_EV_IRQHandler);              // I2C3 event
HANDLER(I2C3_ER_IRQHandler);              // I2C3 error
HANDLER(OTG_HS_EP1_OUT_IRQHandler);       // USB OTG HS End Point 1 Out
HANDLER(OTG_HS_EP1_IN_IRQHandler);        // USB OTG HS End Point 1 In
HANDLER(OTG_HS_WKUP_IRQHandler);          // USB OTG HS Wakeup through EXTI
HANDLER(OTG_HS_IRQHandler);               // USB OTG HS
HANDLER(DCMI_IRQHandler);                 // DCMI
HANDLER(CRYP_IRQHandler);                 // CRYP crypto
HANDLER(HASH_RNG_IRQHandler);             // Hash and Rng
HANDLER(FPU_IRQHandler);                  // FPU
HANDLER(UART7_IRQHandler);                // UART7
HANDLER(UART8_IRQHandler);                // UART8
HANDLER(SPI4_IRQHandler);                 // SPI4
HANDLER(SPI5_IRQHandler);                 // SPI5
HANDLER(SPI6_IRQHandler);                 // SPI6
HANDLER(SAI1_IRQHandler);                 // SAI1
HANDLER(LTDC_IRQHandler);                 // LTDC
HANDLER(LTDC_ER_IRQHandler);              // LTDC error
HANDLER(DMA2D_IRQHandler);                // DMA2D
HANDLER(SAI2_IRQHandler);                 // SAI2
HANDLER(QUADSPI_IRQHandler);              // QUADSPI
HANDLER(LPTIM1_IRQHandler);               // LPTIM1
HANDLER(CEC_IRQHandler);                  // HDMI_CEC
HANDLER(I2C4_EV_IRQHandler);              // I2C4 Event                                             
HANDLER(I2C4_ER_IRQHandler);              // I2C4 Error 
HANDLER(SPDIF_RX_IRQHandler);             // SPDIF_RX

/** stm32f7xx interrupt vector table */
vector *io_vectors[] __attribute__((section(".io_vectors"))) = {
	WWDG_IRQHandler,                   // Window WatchDog
	PVD_IRQHandler,                    // PVD through EXTI Line detection
	TAMP_STAMP_IRQHandler,             // Tamper and TimeStamps through the EXTI line
	RTC_WKUP_IRQHandler,               // RTC Wakeup through the EXTI line
	FLASH_IRQHandler,                  // FLASH
	RCC_IRQHandler,                    // RCC
	EXTI0_IRQHandler,                  // EXTI Line0
	EXTI1_IRQHandler,                  // EXTI Line1
	EXTI2_IRQHandler,                  // EXTI Line2
	EXTI3_IRQHandler,                  // EXTI Line3
	EXTI4_IRQHandler,                  // EXTI Line4
	DMA1_Stream0_IRQHandler,           // DMA1 Stream 0
	DMA1_Stream1_IRQHandler,           // DMA1 Stream 1
	DMA1_Stream2_IRQHandler,           // DMA1 Stream 2
	DMA1_Stream3_IRQHandler,           // DMA1 Stream 3
	DMA1_Stream4_IRQHandler,           // DMA1 Stream 4
	DMA1_Stream5_IRQHandler,           // DMA1 Stream 5
	DMA1_Stream6_IRQHandler,           // DMA1 Stream 6
	ADC_IRQHandler,                    // ADC1, ADC2 and ADC3s
	CAN1_TX_IRQHandler,                // CAN1 TX
	CAN1_RX0_IRQHandler,               // CAN1 RX0
	CAN1_RX1_IRQHandler,               // CAN1 RX1
	CAN1_SCE_IRQHandler,               // CAN1 SCE
	EXTI9_5_IRQHandler,                // External Line[9:5]s
	TIM1_BRK_TIM9_IRQHandler,          // TIM1 Break and TIM9
	TIM1_UP_TIM10_IRQHandler,          // TIM1 Update and TIM10
	TIM1_TRG_COM_TIM11_IRQHandler,     // TIM1 Trigger and Commutation and TIM11
	TIM1_CC_IRQHandler,                // TIM1 Capture Compare
	TIM2_IRQHandler,                   // TIM2
	TIM3_IRQHandler,                   // TIM3
	TIM4_IRQHandler,                   // TIM4
	I2C1_EV_IRQHandler,                // I2C1 Event
	I2C1_ER_IRQHandler,                // I2C1 Error
	I2C2_EV_IRQHandler,                // I2C2 Event
	I2C2_ER_IRQHandler,                // I2C2 Error
	SPI1_IRQHandler,                   // SPI1
	SPI2_IRQHandler,                   // SPI2
	USART1_IRQHandler,                 // USART1
	USART2_IRQHandler,                 // USART2
	USART3_IRQHandler,                 // USART3
	EXTI15_10_IRQHandler,              // External Line[15:10]s
	RTC_Alarm_IRQHandler,              // RTC Alarm (A and B) through EXTI Line
	OTG_FS_WKUP_IRQHandler,            // USB OTG FS Wakeup through EXTI line
	TIM8_BRK_TIM12_IRQHandler,         // TIM8 Break and TIM12
	TIM8_UP_TIM13_IRQHandler,          // TIM8 Update and TIM13
	TIM8_TRG_COM_TIM14_IRQHandler,     // TIM8 Trigger and Commutation and TIM14
	TIM8_CC_IRQHandler,                // TIM8 Capture Compare
	DMA1_Stream7_IRQHandler,           // DMA1 Stream7
	FSMC_IRQHandler,                   // FSMC
	SDMMC1_IRQHandler,                 // SDMMC1
	TIM5_IRQHandler,                   // TIM5
	SPI3_IRQHandler,                   // SPI3
	USART4_IRQHandler,                 // UART4
	USART5_IRQHandler,                 // UART5
	TIM6_DAC_IRQHandler,               // TIM6 and DAC1&2 underrun errors
	TIM7_IRQHandler,                   // TIM7
	DMA2_Stream0_IRQHandler,           // DMA2 Stream 0
	DMA2_Stream1_IRQHandler,           // DMA2 Stream 1
	DMA2_Stream2_IRQHandler,           // DMA2 Stream 2
	DMA2_Stream3_IRQHandler,           // DMA2 Stream 3
	DMA2_Stream4_IRQHandler,           // DMA2 Stream 4
	ETH_IRQHandler,                    // Ethernet
	ETH_WKUP_IRQHandler,               // Ethernet Wakeup through EXTI line
	CAN2_TX_IRQHandler,                // CAN2 TX
	CAN2_RX0_IRQHandler,               // CAN2 RX0
	CAN2_RX1_IRQHandler,               // CAN2 RX1
	CAN2_SCE_IRQHandler,               // CAN2 SCE
	OTG_FS_IRQHandler,                 // USB OTG FS
	DMA2_Stream5_IRQHandler,           // DMA2 Stream 5
	DMA2_Stream6_IRQHandler,           // DMA2 Stream 6
	DMA2_Stream7_IRQHandler,           // DMA2 Stream 7
	USART6_IRQHandler,                 // USART6
	I2C3_EV_IRQHandler,                // I2C3 event
	I2C3_ER_IRQHandler,                // I2C3 error
	OTG_HS_EP1_OUT_IRQHandler,         // USB OTG HS End Point 1 Out
	OTG_HS_EP1_IN_IRQHandler,          // USB OTG HS End Point 1 In
	OTG_HS_WKUP_IRQHandler,            // USB OTG HS Wakeup through EXTI
	OTG_HS_IRQHandler,                 // USB OTG HS
	DCMI_IRQHandler,                   // DCMI
	CRYP_IRQHandler,                   // CRYP crypto
	HASH_RNG_IRQHandler,               // Hash and Rng
	FPU_IRQHandler,                    // FPU
	UART7_IRQHandler,                  // UART7
	UART8_IRQHandler,                  // UART8
	SPI4_IRQHandler,                   // SPI4
	SPI5_IRQHandler,                   // SPI5
	SPI6_IRQHandler,                   // SPI6
	SAI1_IRQHandler,                   // SAI1
	LTDC_IRQHandler,                   // LTDC
	LTDC_ER_IRQHandler,                // LTDC error
	DMA2D_IRQHandler,                  // DMA2D
	SAI2_IRQHandler,                   // SAI2
	QUADSPI_IRQHandler,                // QUADSPI
	LPTIM1_IRQHandler,                 // LPTIM1
	CEC_IRQHandler,                    // HDMI_CEC
	I2C4_EV_IRQHandler,                // I2C4 Event                                             
	I2C4_ER_IRQHandler,                // I2C4 Error 
	SPDIF_RX_IRQHandler,               // SPDIF_RX
};

/**
 * @}
 */