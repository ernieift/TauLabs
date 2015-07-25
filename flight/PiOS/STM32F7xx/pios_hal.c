/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_HAL_HANDLES
 * @brief      unique HAL handles
 * @{
 *
 * @file       pios_hal.c
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2015
 * @brief      collection of global handles for HAL access
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

/**
* @brief This is as replacement for the missing NVIC_Init()
*/
#if defined(STM32F7XX)
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
	if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
	{
		/* Set priority */
		HAL_NVIC_SetPriority(
			NVIC_InitStruct->NVIC_IRQChannel,
			NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority,
			NVIC_InitStruct->NVIC_IRQChannelSubPriority
		);

		/* Enable the selected IRQ Channels */
		HAL_NVIC_EnableIRQ(NVIC_InitStruct->NVIC_IRQChannel);
	}
	else
	{
		/* Disable the selected IRQ Channels */
		HAL_NVIC_DisableIRQ(NVIC_InitStruct->NVIC_IRQChannel);
	}
}
#endif

/**
* @brief This functions hold the global device handels and do the function callbacks
*/

/* IWDG handle */
#ifdef HAL_IWDG_MODULE_ENABLED
static IWDG_HandleTypeDef hiwdg;

IWDG_HandleTypeDef * PIOS_HAL_IWDG_GetHandle()
{
	return &hiwdg;
}
#endif

/* RTC handle */
#ifdef HAL_RTC_MODULE_ENABLED
static RTC_HandleTypeDef hrtc;

RTC_HandleTypeDef * PIOS_HAL_RTC_GetHandle()
{
	return &hrtc;
}
/* RTC interrupt callback */
#if defined(PIOS_INCLUDE_RTC)
#include <pios_rtc_priv.h>
void RTC_WKUP_IRQHandler(void)
{
  HAL_RTCEx_WakeUpTimerIRQHandler(&hrtc);
}
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	PIOS_RTC_irq_handler();
}
#endif
#endif

/* CRC handle */
#ifdef HAL_CRC_MODULE_ENABLED
static CRC_HandleTypeDef hcrc;

CRC_HandleTypeDef * PIOS_HAL_CRC_GetHandle()
{
	return &hcrc;
}
#endif

/* Timer handles */
#ifdef HAL_TIM_MODULE_ENABLED
static TIM_HandleTypeDef htim[PIOS_TIM_MAX_DEVS];

TIM_HandleTypeDef * PIOS_HAL_TIM_FindHandle(TIM_TypeDef *timer)
{
	/* Check the TIM value */
	if (IS_TIM_INSTANCE(timer) == 0)
		return NULL;

	/* Try to find the TIM handle */
	for (uint8_t i = 0; i < PIOS_TIM_MAX_DEVS; i++)
	{
		if (htim[i].Instance == timer)
			return &htim[i];
	}

	/* Found nothing */
	return NULL;
}

TIM_HandleTypeDef * PIOS_HAL_TIM_AllocHandle(TIM_TypeDef *timer)
{
	/* Check the TIM value */
	if (IS_TIM_INSTANCE(timer) == 0)
		return NULL;

	/* Try to find the handle first */
	TIM_HandleTypeDef *tmp = PIOS_HAL_TIM_FindHandle(timer);
	if (tmp)
		return tmp;

	/* Try to find a free TIM handle */
	for (uint8_t i = 0; i < PIOS_TIM_MAX_DEVS; i++)
	{
		if (IS_TIM_INSTANCE(htim[i].Instance) == 0)
			return &htim[i];
	}

	/* No free handle and timer mot found */
	return NULL;
}
#endif
