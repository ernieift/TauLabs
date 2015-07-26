/**
 ******************************************************************************
 *
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_EXTI External Interrupt Handlers
 * @brief External interrupt handler functions
 * @{
 *
 * @file       pios_exti.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2014
 * @brief      External Interrupt Handlers
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

#if defined(PIOS_INCLUDE_EXTI)

#if defined(PIOS_INCLUDE_FREERTOS)
#include "FreeRTOS.h"
#endif /* defined(PIOS_INCLUDE_FREERTOS) */

/* Map EXTI line to full config */
#define EXTI_MAX_LINES 16
#define PIOS_EXTI_INVALID 0xFF
static uint8_t pios_exti_line_to_cfg_map[EXTI_MAX_LINES] = {
	[0 ... EXTI_MAX_LINES-1] = PIOS_EXTI_INVALID,
};

/* Table of exti configs registered at compile time */
extern struct pios_exti_cfg __start__exti __attribute__((weak));
extern struct pios_exti_cfg __stop__exti  __attribute__((weak));

uint8_t PIOS_EXTI_gpio_pin_to_index(uint32_t gpio_pin)
{
	switch((uint32_t)gpio_pin) {
	case GPIO_PIN_0: return 0;
	case GPIO_PIN_1: return 1;
	case GPIO_PIN_2: return 2;
	case GPIO_PIN_3: return 3;
	case GPIO_PIN_4: return 4;
	case GPIO_PIN_5: return 5;
	case GPIO_PIN_6: return 6;
	case GPIO_PIN_7: return 7;
	case GPIO_PIN_8: return 8;
	case GPIO_PIN_9: return 9;
	case GPIO_PIN_10: return 10;
	case GPIO_PIN_11: return 11;
	case GPIO_PIN_12: return 12;
	case GPIO_PIN_13: return 13;
	case GPIO_PIN_14: return 14;
	case GPIO_PIN_15: return 15;
	}

	PIOS_Assert(0);
	return PIOS_EXTI_INVALID;
}

int32_t PIOS_EXTI_Init(const struct pios_exti_cfg * cfg)
{
  	PIOS_Assert(cfg);
	PIOS_Assert(&__start__exti);
	PIOS_Assert(cfg >= &__start__exti);
	PIOS_Assert(cfg < &__stop__exti);

	uint8_t cfg_index = cfg - &__start__exti;

	/* Connect this config to the requested vector */
	uint8_t line_index = PIOS_EXTI_gpio_pin_to_index(cfg->pin.init.Pin);

	if (line_index == PIOS_EXTI_INVALID) {
		/* no direct expression for pin found. Multiple pins are not allowed here */
		goto out_fail;
	}

	if (pios_exti_line_to_cfg_map[line_index] != PIOS_EXTI_INVALID) {
		/* Someone else already has this mapped */
		goto out_fail;
	}

	/* Bind the config to the exti line */
	pios_exti_line_to_cfg_map[line_index] = cfg_index;

	/* Initialize the GPIO pin. User has to care for interrupt definition in GPIO structure */
	HAL_GPIO_Init(cfg->pin.gpio, (GPIO_InitTypeDef*)&cfg->pin.init);

	/* Enable the interrupt channel */
	NVIC_Init((NVIC_InitTypeDef*)&cfg->irq.init);

	return 0;

out_fail:
	return -1;
}

static bool PIOS_EXTI_generic_irq_handler(uint8_t line_index)
{
	uint8_t cfg_index = pios_exti_line_to_cfg_map[line_index];

	PIOS_Assert(&__start__exti);

	if (cfg_index > NELEMENTS(pios_exti_line_to_cfg_map) ||
		cfg_index == PIOS_EXTI_INVALID) {
		/* Unconfigured interrupt just fired! */
		return false;
	}

	struct pios_exti_cfg * cfg = &__start__exti + cfg_index;
	return cfg->vector();
}

/* Bind Interrupt Handlers */

#if defined(PIOS_INCLUDE_FREERTOS)
#define PIOS_EXTI_HANDLE_LINE(line, woken)								\
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_##line) != RESET) {				\
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_##line);						\
		woken = PIOS_EXTI_generic_irq_handler(line) ? pdTRUE : woken;	\
    }
#else
#define PIOS_EXTI_HANDLE_LINE(line, woken)								\
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_##line) != RESET {				\
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_##line);						\
		PIOS_EXTI_generic_irq_handler(line);							\
	}
#endif

static void PIOS_EXTI_0_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(0, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI0_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_0_irq_handler")));

static void PIOS_EXTI_1_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(1, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI1_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_1_irq_handler")));

static void PIOS_EXTI_2_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(2, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI2_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_2_irq_handler")));

static void PIOS_EXTI_3_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(3, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI3_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_3_irq_handler")));

static void PIOS_EXTI_4_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(4, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI4_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_4_irq_handler")));

static void PIOS_EXTI_9_5_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(5, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(6, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(7, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(8, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(9, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI9_5_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_9_5_irq_handler")));

static void PIOS_EXTI_15_10_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

#if defined(PIOS_INCLUDE_FREERTOS)
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
#else
	bool xHigherPriorityTaskWoken;
#endif
	PIOS_EXTI_HANDLE_LINE(10, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(11, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(12, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(13, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(14, xHigherPriorityTaskWoken);
	PIOS_EXTI_HANDLE_LINE(15, xHigherPriorityTaskWoken);
#if defined(PIOS_INCLUDE_FREERTOS)
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
#else
	(void)xHigherPriorityTaskWoken;
#endif

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
void EXTI15_10_IRQHandler(void) __attribute__ ((alias ("PIOS_EXTI_15_10_irq_handler")));

#endif /* PIOS_INCLUDE_EXTI */

/**
  * @}
  * @}
  */
