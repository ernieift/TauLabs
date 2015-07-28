/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_SYS System Functions
 * @brief PIOS System Initialization code
 * @{
 *
 * @file       pios_sys.c
 * @author     Michael Smith Copyright (C) 2011
 * 			The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2014-15
 * @brief      Sets up basic STM32 system hardware, functions are called from Main.
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

/* Project Includes */
#include "pios.h"

#if defined(PIOS_INCLUDE_SYS)

/* Private Function Prototypes */
void NVIC_Configuration(void);
void SysTick_Handler(void);

/* Local Macros */
#define MEM8(addr)  (*((volatile uint8_t  *)(addr)))
#define MEM16(addr)  (*((volatile uint16_t  *)(addr)))
#define MEM32(addr)  (*((volatile uint32_t  *)(addr)))

/**
* Initialises all system peripherals
*/
void PIOS_SYS_Init(void)
{
#if !defined(PIOS_INCLUDE_CHIBIOS)
	/* Setup STM32 system (RCC, clock, PLL and Flash configuration) - CMSIS Function */
	SystemInit();
	SystemCoreClockUpdate();	/* update SystemCoreClock for use elsewhere */
#endif /* !defined(PIOS_INCLUDE_CHIBIOS) */

	/*
	 * @todo might make sense to fetch the bus clocks and save them somewhere to avoid
	 * having to use the clunky get-all-clocks API everytime we need one.
	 */

	/* Initialise Basic NVIC */
	/* do this early to ensure that we take exceptions in the right place */
	NVIC_Configuration();

	/* Init the delay system */
	PIOS_DELAY_Init();

	/*
	 * Turn on all the peripheral clocks.
	 * Micromanaging clocks makes no sense given the power situation in the system, so
	 * light up everything we might reasonably use here and just leave it on.
	 */
	do { __IO uint32_t tmpreg; SET_BIT(RCC->AHB1ENR,
			RCC_AHB1ENR_GPIOAEN |
			RCC_AHB1ENR_GPIOBEN |
			RCC_AHB1ENR_GPIOCEN |
			RCC_AHB1ENR_GPIODEN |
			RCC_AHB1ENR_GPIOEEN |
			RCC_AHB1ENR_GPIOFEN |
			RCC_AHB1ENR_GPIOGEN |
			RCC_AHB1ENR_GPIOHEN |
			RCC_AHB1ENR_GPIOIEN |
			RCC_AHB1ENR_GPIOJEN |
			RCC_AHB1ENR_GPIOKEN |
			RCC_AHB1ENR_CRCEN |
			RCC_AHB1ENR_BKPSRAMEN |
			RCC_AHB1ENR_DTCMRAMEN |
			RCC_AHB1ENR_DMA1EN |
			RCC_AHB1ENR_DMA2EN |
			RCC_AHB1ENR_DMA2DEN |
			//RCC_AHB1ENR_ETHMACEN |			No ethernet
			//RCC_AHB1ENR_ETHMACTXEN |
			//RCC_AHB1ENR_ETHMACRXEN |
			//RCC_AHB1ENR_ETHMACPTPEN |
			//RCC_AHB1ENR_OTGHSEN |				No high-speed USB (requires external PHY)
			//RCC_AHB1ENR_OTGHSULPIEN |			No ULPI PHY (see above)
		0); tmpreg = READ_BIT(RCC->AHB1ENR, 1); UNUSED(tmpreg);
	} while(0);

	do { __IO uint32_t tmpreg; SET_BIT(RCC->AHB2ENR,
			// RCC_AHB2ENR_DCMIEN |			No camera   @todo might make sense later for basic vision support?
			// RCC_AHB2ENR_CRYPEN |			No crypto
			// RCC_AHB2ENR_HASHEN |			No hash generator
			// RCC_AHB2ENR_RNGEN |			No random numbers @todo might be good to have later if entropy is desired
			// RCC_AHB2ENR_OTGFSEN |
		0); tmpreg = READ_BIT(RCC->AHB2ENR, 1); UNUSED(tmpreg);
	} while(0);

	do { __IO uint32_t tmpreg; SET_BIT(RCC->AHB3ENR,
			// RCC_AHB3ENR_FMCEN |			No external static memory
			// RCC_AHB3ENR_QSPIEN |			No Queued SPI
		0); tmpreg = READ_BIT(RCC->AHB3ENR, 1); UNUSED(tmpreg);
	} while(0);

	do { __IO uint32_t tmpreg; SET_BIT(RCC->APB1ENR,
			RCC_APB1ENR_TIM2EN |
			RCC_APB1ENR_TIM3EN |
			RCC_APB1ENR_TIM4EN |
			RCC_APB1ENR_TIM5EN |
			RCC_APB1ENR_TIM6EN |
			RCC_APB1ENR_TIM7EN |
			RCC_APB1ENR_TIM12EN |
			RCC_APB1ENR_TIM13EN |
			RCC_APB1ENR_TIM14EN |
			// RCC_APB1ENR_LPTIM1EN |
			RCC_APB1ENR_WWDGEN |
			RCC_APB1ENR_SPI2EN |
			RCC_APB1ENR_SPI3EN |
			// RCC_APB1ENR_SPDIFRXEN |
			RCC_APB1ENR_USART2EN |
			RCC_APB1ENR_USART3EN |
			RCC_APB1ENR_UART4EN |
			RCC_APB1ENR_UART5EN |
			RCC_APB1ENR_I2C1EN |
			RCC_APB1ENR_I2C2EN |
			RCC_APB1ENR_I2C4EN |
			RCC_APB1ENR_CAN1EN |
			RCC_APB1ENR_CAN2EN |
			RCC_APB1ENR_CECEN |
			RCC_APB1ENR_PWREN |
			RCC_APB1ENR_DACEN |
			RCC_APB1ENR_UART7EN |
			RCC_APB1ENR_UART8EN |
		0); tmpreg = READ_BIT(RCC->APB1ENR, 1); UNUSED(tmpreg);
	} while(0);

	do { __IO uint32_t tmpreg; SET_BIT(RCC->APB2ENR,
			RCC_APB2ENR_TIM1EN |
			RCC_APB2ENR_TIM8EN |
			RCC_APB2ENR_USART1EN |
			RCC_APB2ENR_USART6EN |
			RCC_APB2ENR_ADC1EN |
			RCC_APB2ENR_ADC2EN |
			RCC_APB2ENR_ADC3EN |
			RCC_APB2ENR_SDMMC1EN |
			RCC_APB2ENR_SPI1EN |
			RCC_APB2ENR_SPI4EN |
			RCC_APB2ENR_SYSCFGEN |
			RCC_APB2ENR_TIM9EN |
			RCC_APB2ENR_TIM10EN |
			RCC_APB2ENR_TIM11EN |
			RCC_APB2ENR_SPI5EN |
			RCC_APB2ENR_SPI6EN |
			RCC_APB2ENR_SAI1EN |
			RCC_APB2ENR_SAI2EN |
			RCC_APB2ENR_LTDCEN |
		0); tmpreg = READ_BIT(RCC->APB2ENR, 1); UNUSED(tmpreg);
	} while(0);

	/*
	 * Configure all pins as input / pullup to avoid issues with
	 * uncommitted pins, excepting special-function pins that we need to
	 * remain as-is.
	 */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_All;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;

#if (PIOS_USB_ENABLED)
	GPIO_InitStructure.Pin &= ~(GPIO_PIN_11 | GPIO_PIN_12);				// leave USB D+/D- alone
#endif
	GPIO_InitStructure.Pin &= ~(GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);	// leave JTAG pins alone
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_All;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOI, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOJ, &GPIO_InitStructure);
	HAL_GPIO_Init(GPIOK, &GPIO_InitStructure);
}

/**
* Shutdown PIOS and reset the microcontroller:<BR>
* <UL>
*   <LI>Disable all RTOS tasks
*   <LI>Disable all interrupts
*   <LI>Turn off all board LEDs
*   <LI>Reset STM32
* </UL>
* \return < 0 if reset failed
*/
int32_t PIOS_SYS_Reset(void)
{
	// disable all interrupts
	PIOS_IRQ_Disable();

	// turn off all board LEDs
#if defined(PIOS_LED_HEARTBEAT)
	PIOS_LED_Off(PIOS_LED_HEARTBEAT);
#endif	/* PIOS_LED_HEARTBEAT */
#if defined(PIOS_LED_ALARM)
	PIOS_LED_Off(PIOS_LED_ALARM);
#endif	/* PIOS_LED_ALARM */

	/* XXX F10x port resets most (but not all) peripherals ... do we care? */

	/* Reset STM32 */
	NVIC_SystemReset();

	while (1) ;

	/* We will never reach this point */
	return -1;
}

/**
* Returns the CPU's flash size (in bytes)
*/
uint32_t PIOS_SYS_getCPUFlashSize(void)
{
	return ((uint32_t) MEM16(0x1fff7a22) * 1024);
}

/**
 * Returns the serial number as byte array
 * param[out] pointer to a byte array which can store at least 12 bytes
 * (12 bytes returned for STM32)
 * return < 0 if feature not supported
 */
int32_t PIOS_SYS_SerialNumberGetBinary(uint8_t *array)
{
	int i;
	
	/* Stored in the so called "electronic signature" */
	for (i = 0; i < PIOS_SYS_SERIAL_NUM_BINARY_LEN; ++i) {
		uint8_t b = MEM8(0x1fff7a10 + i);
		
		array[i] = b;
	}
	
	/* No error */
	return 0;
}

/**
* Returns the serial number as a string
* param[out] str pointer to a string which can store at least 32 digits + zero terminator!
* (24 digits returned for STM32)
* return < 0 if feature not supported
*/
int32_t PIOS_SYS_SerialNumberGet(char *str)
{
	int i;

	/* Stored in the so called "electronic signature" */
	for (i = 0; i < PIOS_SYS_SERIAL_NUM_ASCII_LEN; ++i) {
		uint8_t b = MEM8(0x1fff7a10 + (i / 2));
		if (!(i & 1))
			b >>= 4;
		b &= 0x0f;

		str[i] = ((b > 9) ? ('A' - 10) : '0') + b;
	}
	str[i] = '\0';

	/* No error */
	return 0;
}

/**
* Configures Vector Table base location and SysTick
*/
void NVIC_Configuration(void)
{
	/* Set the Vector Table base address as specified in .ld file */
	extern void *pios_isr_vector_table_base;
	SCB->VTOR = (uint32_t)&pios_isr_vector_table_base;

	/* 4 bits for Interrupt priorities so no sub priorities */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* Configure HCLK clock as SysTick clock source. */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

#ifdef USE_FULL_ASSERT
/**
* Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* \param[in]  file pointer to the source file name
* \param[in]  line assert_param error line source number
* \retval None
*/
void assert_failed(uint8_t * file, uint32_t line)
{
	/* When serial debugging is implemented, use something like this. */
	/* printf("Wrong parameters value: file %s on line %d\r\n", file, line); */

	/* Setup the LEDs to Alternate */
#if defined(PIOS_LED_HEARTBEAT)
	PIOS_LED_On(PIOS_LED_HEARTBEAT);
#endif	/* PIOS_LED_HEARTBEAT */
#if defined(PIOS_LED_ALARM)
	PIOS_LED_Off(PIOS_LED_ALARM);
#endif	/* PIOS_LED_ALARM */

	/* Infinite loop */
	while (1) {
#if defined(PIOS_LED_HEARTBEAT)
		PIOS_LED_Toggle(PIOS_LED_HEARTBEAT);
#endif	/* PIOS_LED_HEARTBEAT */
#if defined(PIOS_LED_ALARM)
		PIOS_LED_Toggle(PIOS_LED_ALARM);
#endif	/* PIOS_LED_ALARM */
		for (int i = 0; i < 1000000; i++) ;
	}
}
#endif

#endif

/**
  * @}
  * @}
  */
