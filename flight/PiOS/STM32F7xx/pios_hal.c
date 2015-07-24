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

// IWDG handle
#ifdef HAL_IWDG_MODULE_ENABLED
IWDG_HandleTypeDef hiwdg;
#endif

// RTC handle
#ifdef HAL_RTC_MODULE_ENABLED
RTC_HandleTypeDef hrtc;
#endif

// CRC handle
#ifdef HAL_CRC_MODULE_ENABLED
CRC_HandleTypeDef hcrc;
#endif
