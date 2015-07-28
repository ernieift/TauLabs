/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup   PIOS_PWM PWM Functions
 * @brief PIOS interface to read and write from servo PWM ports
 * @{
 *
 * @file       pios_ppm_priv.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2015
 * @brief      ppm private structures.
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

#ifndef PIOS_PWM_PRIV_H
#define PIOS_PWM_PRIV_H

#include <pios.h>
#include <pios_stm32.h>

struct pios_pwm_cfg {
	TIM_IC_InitTypeDef tim_ic_init;
	const struct pios_tim_channel * channels;
	uint8_t num_channels;
};

extern const struct pios_rcvr_driver pios_pwm_rcvr_driver;

extern int32_t PIOS_PWM_Init(uintptr_t * pwm_id, const struct pios_pwm_cfg * cfg);

#endif /* PIOS_PWM_PRIV_H */

/**
 * @}
 * @}
 */
