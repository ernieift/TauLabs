/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup   MISC Functions
 * @brief PIOS misc function for support the STM32F7xx
 * @{
 *
 * @file       misc.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2015
 * @brief      misc private definitions.
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

#ifndef __MISC_H
#define __MISC_H

typedef enum
{ 
  Bit_RESET = GPIO_PIN_RESET,
  Bit_SET = GPIO_PIN_SET
} BitAction;

typedef struct
{
  IRQn_Type  NVIC_IRQChannel;
  uint32_t NVIC_IRQChannelPreemptionPriority;
  uint32_t NVIC_IRQChannelSubPriority;
  FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;

extern void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);

#endif /* __MISC_H */

/**
  * @}
  */
