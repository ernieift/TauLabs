/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup   PIOS_TIMER Timer Functions
 * @brief PIOS interface to read and write from servo PWM ports
 * @{
 *
 * @file       pios_servo_priv.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2015
 * @brief      Servo private structures.
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

#ifndef PIOS_TIM_PRIV_H
#define PIOS_TIM_PRIV_H

#include <pios_stm32.h>

struct pios_tim_clock_cfg {
	TIM_TypeDef * timer;
	const TIM_Base_InitTypeDef * time_base_init;
	struct stm32_irq irq;
	struct stm32_irq irq2;
};

struct pios_tim_channel {
	TIM_TypeDef * timer;
	uint8_t timer_chan;

	struct stm32_gpio pin;
};

struct pios_tim_callbacks {
	void (*overflow)(uintptr_t tim_id, uintptr_t context, uint8_t chan_idx, uint16_t count);
	void (*edge)(uintptr_t tim_id, uintptr_t context, uint8_t chan_idx, uint16_t count);
};

extern int32_t PIOS_TIM_InitClock(const struct pios_tim_clock_cfg * cfg);
extern int32_t PIOS_TIM_InitChannels(uintptr_t * tim_id, const struct pios_tim_channel * channels, uint8_t num_channels, const struct pios_tim_callbacks * callbacks, uintptr_t context);

#endif	/* PIOS_TIM_PRIV_H */

/**
 * @}
 * @}
 */
