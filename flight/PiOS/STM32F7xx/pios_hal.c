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


