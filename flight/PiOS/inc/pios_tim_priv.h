#ifndef PIOS_TIM_PRIV_H
#define PIOS_TIM_PRIV_H

#include <pios_stm32.h>

struct pios_tim_clock_cfg {
	TIM_TypeDef * timer;
#if defined(STM32F7XX)
	const TIM_Base_InitTypeDef * time_base_init;
#else
	const TIM_TimeBaseInitTypeDef * time_base_init;
#endif
	struct stm32_irq irq;
	struct stm32_irq irq2;
};

struct pios_tim_channel {
	TIM_TypeDef * timer;
	uint8_t timer_chan;

	struct stm32_gpio pin;
#ifndef STM32F7XX
	uint32_t remap;
#endif
};

struct pios_tim_callbacks {
	void (*overflow)(uintptr_t tim_id, uintptr_t context, uint8_t chan_idx, uint16_t count);
	void (*edge)(uintptr_t tim_id, uintptr_t context, uint8_t chan_idx, uint16_t count);
};

extern int32_t PIOS_TIM_InitClock(const struct pios_tim_clock_cfg * cfg);
extern int32_t PIOS_TIM_InitChannels(uintptr_t * tim_id, const struct pios_tim_channel * channels, uint8_t num_channels, const struct pios_tim_callbacks * callbacks, uintptr_t context);

#endif	/* PIOS_TIM_PRIV_H */
