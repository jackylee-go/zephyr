/*
 * Copyright (c) 2026 Egis Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
#include <pinctrl_soc.h>
#include <zephyr/drivers/pinctrl.h>
#include <et171_aosmu.h>

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt,
			   uintptr_t reg)
{
	ARG_UNUSED(reg);

	for (uint8_t i = 0; i < pin_cnt; i++) {
		unsigned int key;
		const uint32_t pin_cfg = pins[i];
		const uint32_t reg_sel = (pin_cfg >> 24) & 0xFF;
		const uint32_t pos_offset = (pin_cfg >> 16) & 0xFF;
		const uint32_t mux_sel = ((pin_cfg >> 8) & 0xFF) << pos_offset;
		const uint32_t mux_mask = (0x03 << pos_offset);
		const uint32_t mux_reg = (reg_sel == 0)
			? SMU2_REG_PAD_MUXA : SMU2_REG_PAD_MUXB;

		key = arch_irq_lock();
		WRITE_SMU2_REG(
			mux_reg,
			(READ_SMU2_REG(mux_reg) & ~mux_mask) | mux_sel
		);
		arch_irq_unlock(key);
	}

	return 0;
}
