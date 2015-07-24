/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup   PIOS_PWM PWM Input Functions
 * @brief		Code to measure with PWM input
 * @{
 *
 * @file       pios_pwm.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      PWM Input functions (STM32 dependent)
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

#if defined(PIOS_INCLUDE_RTC)
#include <pios_rtc_priv.h>

#ifndef PIOS_RTC_PRESCALER
#define PIOS_RTC_PRESCALER 100
#endif

struct rtc_callback_entry {
  void (*fn)(uintptr_t);
  uintptr_t data;
};

extern RTC_HandleTypeDef hrtc;

#define PIOS_RTC_MAX_CALLBACKS 3
struct rtc_callback_entry rtc_callback_list[PIOS_RTC_MAX_CALLBACKS];
static uint8_t rtc_callback_next = 0;

void PIOS_RTC_Init(const struct pios_rtc_cfg * cfg)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {
		.PeriphClockSelection = RCC_PERIPHCLK_RTC,
		.RTCClockSelection = cfg->clksrc
	};
	// configure RTC clock to get 1000kHz
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	// initialize RTC
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	HAL_RTC_Init(&hrtc);

	// configure RTC to get finaly a 625Hz interval and enable WakeUp interrupt
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, cfg->prescaler, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
}

uint32_t PIOS_RTC_Counter()
{
	return HAL_RTCEx_GetWakeUpTimer(&hrtc);
}

/* FIXME: This shouldn't use hard-coded clock rates, dividers or prescalers.
 *        Should get these from the cfg struct passed to init.
 */
float PIOS_RTC_Rate()
{
	return (float) (8e6 / 128) / (1 + PIOS_RTC_PRESCALER);
}

float PIOS_RTC_MsPerTick() 
{
	return 1000.0f / PIOS_RTC_Rate();
}

/* TODO: This needs a mutex around rtc_callbacks[] */
bool PIOS_RTC_RegisterTickCallback(void (*fn)(uintptr_t id), uintptr_t data)
{
	struct rtc_callback_entry * cb;
	if (rtc_callback_next >= PIOS_RTC_MAX_CALLBACKS) {
		return false;
	}

	cb = &rtc_callback_list[rtc_callback_next++];

	cb->fn   = fn;
	cb->data = data;
	return true;
}

void PIOS_RTC_irq_handler (void)
{
#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_PROLOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */

	if (__HAL_RTC_WAKEUPTIMER_GET_IT(&hrtc, RTC_IT_WUT) )
	{
		/* Get the status of the Interrupt */
		if (__HAL_RTC_WAKEUPTIMER_GET_IT_SOURCE(&hrtc, RTC_IT_WUT) )
		{
			/* Call all registered WAKEUPTIMER callbacks */
			for (uint8_t i = 0; i < rtc_callback_next; i++)
			{
				struct rtc_callback_entry * cb = &rtc_callback_list[i];
				if (cb->fn) {
					(cb->fn)(cb->data);
				}
			}

		/* Clear the WAKEUPTIMER interrupt pending bit */
		__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
		}
	}

	/* Clear the EXTI's line Flag for RTC WakeUpTimer */
	__HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();

	/* Change RTC state */
	hrtc.State = HAL_RTC_STATE_READY;

#if defined(PIOS_INCLUDE_CHIBIOS)
	CH_IRQ_EPILOGUE();
#endif /* defined(PIOS_INCLUDE_CHIBIOS) */
}
#endif

/** 
 * @}
 * @}
 */
