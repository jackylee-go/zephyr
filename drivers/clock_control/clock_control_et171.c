/*
 * Copyright (c) 2026, Egis Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT egis_et171_clock

#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/drivers/clock_control/clock_control_et171.h>
#include <et171_aosmu.h>
#include <et171_otp.h>

#define AHB_CLOCK_MASK (0                  \
		| BIT(ET171_CLOCK_SYSRAM)  \
		| BIT(ET171_CLOCK_SYSRAM2) \
		| BIT(ET171_CLOCK_SYSRAM3) \
		| BIT(ET171_CLOCK_SPIM1)   \
		| BIT(ET171_CLOCK_SPIM2)   \
		| BIT(ET171_CLOCK_SPIM3)   \
		| BIT(ET171_CLOCK_SPIS)    \
		| BIT(ET171_CLOCK_CRYPTO)  \
		| BIT(ET171_CLOCK_DMAC)    \
		| BIT(ET171_CLOCK_USB2)    \
		| BIT(ET171_CLOCK_HWA)     \
		| BIT(ET171_CLOCK_HWA2)    \
		| BIT(ET171_CLOCK_AHB)     \
		| BIT(ET171_CLOCK_CPU)     \
	)

#define APB_CLOCK_MASK (0                  \
		| BIT(ET171_CLOCK_GPIO)    \
		| BIT(ET171_CLOCK_PITPWM)  \
		| BIT(ET171_CLOCK_I2C)     \
		| BIT(ET171_CLOCK_UART)    \
		| BIT(ET171_CLOCK_OTPC)    \
		| BIT(ET171_CLOCK_WDT)     \
		| BIT(ET171_CLOCK_RTC)     \
		| BIT(ET171_CLOCK_APB)     \
	)

#define CTRL_CLOCK_MASK (0                 \
		| BIT(ET171_CLOCK_SYSRAM)  \
		| BIT(ET171_CLOCK_SYSRAM2) \
		| BIT(ET171_CLOCK_SYSRAM3) \
		| BIT(ET171_CLOCK_SPIM1)   \
		| BIT(ET171_CLOCK_SPIM2)   \
		| BIT(ET171_CLOCK_SPIM3)   \
		| BIT(ET171_CLOCK_SPIS)    \
		| BIT(ET171_CLOCK_CRYPTO)  \
		| BIT(ET171_CLOCK_DMAC)    \
		| BIT(ET171_CLOCK_USB2)    \
		| BIT(ET171_CLOCK_HWA)     \
		| BIT(ET171_CLOCK_HWA2)    \
		| BIT(ET171_CLOCK_GPIO)    \
		| BIT(ET171_CLOCK_PITPWM)  \
		| BIT(ET171_CLOCK_I2C)     \
		| BIT(ET171_CLOCK_UART)    \
		| BIT(ET171_CLOCK_OTPC)    \
		| BIT(ET171_CLOCK_WDT)     \
		| BIT(ET171_CLOCK_RTC)     \
	)


/* ========================================================= driver instance */
struct et171_clock_data {
	uint32_t root_clock;
	uint32_t ext_clock;
};

static uint32_t get_bus_speed(struct et171_clock_data *data, uint32_t is_apb)
{
	uint32_t clk_cfg = READ_AOSMU_REG(AOSMU_REG_CLK_SRC);
	uint32_t clk_req = (SMU_CLK_SRC_250M == (clk_cfg & SMU_CLK_SRC_SEL)) ?
		       data->root_clock : data->ext_clock;

	switch (clk_cfg & SMU_CLK_SRC_AHB_DIV_MASK) {
	case SMU_CLK_SRC_AHB_DIV_1:
		break;
	case SMU_CLK_SRC_AHB_DIV_2:
		clk_req /= 2;
		break;
	case SMU_CLK_SRC_AHB_DIV_3:
		clk_req /= 3;
		break;
	case SMU_CLK_SRC_AHB_DIV_4:
		clk_req /= 4;
		break;
	case SMU_CLK_SRC_AHB_DIV_6:
		clk_req /= 6;
		break;
	case SMU_CLK_SRC_AHB_DIV_8:
		clk_req /= 8;
		break;
	case SMU_CLK_SRC_AHB_DIV_16:
		clk_req /= 16;
		break;
	default:
		break;
	}

	if (is_apb) {
		switch (clk_cfg & SMU_CLK_SRC_APB_DIV_MASK) {
		case SMU_CLK_SRC_APB_DIV_1:
			clk_req /= 2 * 1;
			break;
		case SMU_CLK_SRC_APB_DIV_2:
			clk_req /= 2 * 2;
			break;
		case SMU_CLK_SRC_APB_DIV_3:
			clk_req /= 2 * 3;
			break;
		case SMU_CLK_SRC_APB_DIV_4:
			clk_req /= 2 * 4;
			break;
		case SMU_CLK_SRC_APB_DIV_6:
			clk_req /= 2 * 6;
			break;
		case SMU_CLK_SRC_APB_DIV_8:
			clk_req /= 2 * 8;
			break;
		case SMU_CLK_SRC_APB_DIV_16:
			clk_req /= 2 * 16;
			break;
		default:
			clk_req /= 2 * 1;
			break;
		}
	}

	return clk_req;
}

static int et171_clock_control_on(const struct device *dev,
				  clock_control_subsys_t sub_system)
{
	const uint32_t clkid = 1 << (uint32_t)sub_system;
	unsigned int key;

	ARG_UNUSED(dev);

	if (clkid & CTRL_CLOCK_MASK) {
		key = arch_irq_lock();
		WRITE_AOSMU_REG(AOSMU_CLK_EN, READ_AOSMU_REG(AOSMU_CLK_EN) | clkid);
		arch_irq_unlock(key);
	} else {
		return -EINVAL;
	}

	return 0;
}

static int et171_clock_control_off(const struct device *dev,
				   clock_control_subsys_t sub_system)
{
	const uint32_t clkid = 1 << (uint32_t)sub_system;
	unsigned int key;

	ARG_UNUSED(dev);

	if (clkid & CTRL_CLOCK_MASK) {
		key = arch_irq_lock();
		WRITE_AOSMU_REG(AOSMU_CLK_EN, READ_AOSMU_REG(AOSMU_CLK_EN) & ~clkid);
		arch_irq_unlock(key);
	} else {
		return -EINVAL;
	}

	return 0;
}

static int et171_clock_control_get_rate(const struct device *dev,
					clock_control_subsys_t sub_system,
					uint32_t *rate)
{
	struct et171_clock_data *data = dev->data;
	const uint32_t clkid = 1 << (uint32_t)sub_system;

	if (0 == (clkid & (AHB_CLOCK_MASK | APB_CLOCK_MASK))) {
		return -EINVAL;
	}

	*rate = get_bus_speed(data, (clkid & APB_CLOCK_MASK));

	return 0;
}

static int et171_clock_init(const struct device *dev)
{
	struct et171_clock_data *data = dev->data;

	data->root_clock = et171_otp_get_root_clock();
	if (0 == data->root_clock) {
		data->root_clock = 205 * 10000000;
	}
	data->ext_clock = 32768;

	return 0;
}

static DEVICE_API(clock_control, et171_clock_control_api) = {
	.on = et171_clock_control_on,
	.off = et171_clock_control_off,
	.get_rate = et171_clock_control_get_rate,
};

static struct et171_clock_data clock_data;

DEVICE_DT_INST_DEFINE(0,
		      et171_clock_init,
		      NULL,
		      &clock_data, NULL,
		      PRE_KERNEL_1, CONFIG_CLOCK_CONTROL_INIT_PRIORITY,
		      &et171_clock_control_api);
