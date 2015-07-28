/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup misc
 * @brief      add misc functions to HAL library
 * @{
 *
 * @file       misc.c
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
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before. 
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
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
