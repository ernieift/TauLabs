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

#ifndef PIOS_HAL_H
#define PIOS_HAL_H

/* Public Functions */

#ifdef HAL_IWDG_MODULE_ENABLED
extern IWDG_HandleTypeDef * PIOS_HAL_IWDG_GetHandle();
#endif

#ifdef HAL_RTC_MODULE_ENABLED
extern RTC_HandleTypeDef * PIOS_HAL_RTC_GetHandle();
#endif

#ifdef HAL_CRC_MODULE_ENABLED
extern CRC_HandleTypeDef * PIOS_HAL_CRC_GetHandle();
#endif

#endif /* PIOS_HAL_H */

/**
  * @}
  * @}
  */
