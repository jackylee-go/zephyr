/*
 * Copyright (c) 2025 Egis Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <et171_aosmu.h>
#include <et171_otp.h>

static void et171_config_soc_clock(void)
{
#define AHB_SOURCE_CLOCK (205 * 1000000) /* 205MHz */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(clock), okay)
/*  If clock node is ready. */
#   if DT_NODE_HAS_PROP(DT_NODELABEL(clock), ahb_divide)
	/* If property clock::ahb_divide is existed. */
#       if DT_PROP(DT_NODELABEL(clock), ahb_divide) == 1
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_1
#       elif DT_PROP(DT_NODELABEL(clock), ahb_divide) == 2
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_2
#       elif DT_PROP(DT_NODELABEL(clock), ahb_divide) == 3
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_3
#       elif DT_PROP(DT_NODELABEL(clock), ahb_divide) == 4
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_4
#       elif DT_PROP(DT_NODELABEL(clock), ahb_divide) == 6
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_6
#       elif DT_PROP(DT_NODELABEL(clock), ahb_divide) == 8
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_8
#       elif DT_PROP(DT_NODELABEL(clock), ahb_divide) == 16
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_16
#       else
#           error "invalid property value of ahb-divide"
#       endif
#       define AHB_CLOCK_DIV DT_PROP(DT_NODELABEL(clock), ahb_divide)
#       define AHB_CLOCK (AHB_SOURCE_CLOCK / AHB_CLOCK_DIV)
#   elif DT_NODE_HAS_PROP(DT_NODELABEL(clock), ahb_clock)
	/* If property `clock::ahb_clock` is existed,
	 * choose an appropriate divisor for the specified `ahb_clock`.
	 */
#       define AHB_CLOCK DT_PROP(DT_NODELABEL(clock), ahb_clock)
#       define AHB_CLOCK_BOUNDARY(div1, div2) \
	    (((AHB_SOURCE_CLOCK / (div1)) + (AHB_SOURCE_CLOCK / (div2))) / 2)
#       if AHB_CLOCK > AHB_CLOCK_BOUNDARY(1, 2)
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_1
#           define AHB_CLOCK_DIV 1
#       elif AHB_CLOCK > AHB_CLOCK_BOUNDARY(2, 3)
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_2
#           define AHB_CLOCK_DIV 2
#       elif AHB_CLOCK > AHB_CLOCK_BOUNDARY(3, 4)
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_3
#           define AHB_CLOCK_DIV 3
#       elif AHB_CLOCK > AHB_CLOCK_BOUNDARY(4, 6)
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_4
#           define AHB_CLOCK_DIV 4
#       elif AHB_CLOCK > AHB_CLOCK_BOUNDARY(6, 8)
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_6
#           define AHB_CLOCK_DIV 6
#       elif AHB_CLOCK > AHB_CLOCK_BOUNDARY(8, 16)
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_8
#           define AHB_CLOCK_DIV 8
#       else /* AHB_CLOCK > (AHB_SOURCE_CLOCK / 16) or others */
#           define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_16
#           define AHB_CLOCK_DIV 16
#       endif
#   endif
#endif
#ifndef SET_AHB_DIV
#   define SET_AHB_DIV SMU_CLK_SRC_AHB_DIV_3 /* default */
#   define AHB_CLOCK_DIV 3
#   define AHB_CLOCK (AHB_SOURCE_CLOCK / AHB_CLOCK_DIV)
#endif

#define APB_SOURCE_CLOCK (AHB_CLOCK / 2)
#if DT_NODE_HAS_STATUS(DT_NODELABEL(clock), okay)
/*  If clock node is ready. */
#   if DT_NODE_HAS_PROP(DT_NODELABEL(clock), apb_divide)
	/* If property clock::apb_divide is existed. */
#       if DT_PROP(DT_NODELABEL(clock), apb_divide) == 1
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_1
#       elif DT_PROP(DT_NODELABEL(clock), apb_divide) == 2
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_2
#       elif DT_PROP(DT_NODELABEL(clock), apb_divide) == 3
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_3
#       elif DT_PROP(DT_NODELABEL(clock), apb_divide) == 4
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_4
#       elif DT_PROP(DT_NODELABEL(clock), apb_divide) == 6
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_6
#       elif DT_PROP(DT_NODELABEL(clock), apb_divide) == 8
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_8
#       elif DT_PROP(DT_NODELABEL(clock), apb_divide) == 16
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_16
#       else
#           error "invalid property value of apb-divide"
#       endif
#       define APB_CLOCK_DIV DT_PROP(DT_NODELABEL(clock), apb_divide)
#       define APB_CLOCK (APB_SOURCE_CLOCK / APB_CLOCK_DIV)
#   elif DT_NODE_HAS_PROP(DT_NODELABEL(clock), apb_clock)
	/* If property `clock::apb_clock` is existed,
	 * choose an appropriate divisor for the specified `apb_clock`.
	 */
#       define APB_CLOCK DT_PROP(DT_NODELABEL(clock), apb_clock)
#       define APB_CLOCK_BOUNDARY(div1, div2) \
	    (((APB_SOURCE_CLOCK / (div1)) + (APB_SOURCE_CLOCK / (div2))) / 2)
#       if AHB_CLOCK > APB_CLOCK_BOUNDARY(1, 2)
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_1
#           define APB_CLOCK_DIV 1
#       elif AHB_CLOCK > APB_CLOCK_BOUNDARY(2, 3)
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_2
#           define APB_CLOCK_DIV 2
#       elif AHB_CLOCK > APB_CLOCK_BOUNDARY(3, 4)
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_3
#           define APB_CLOCK_DIV 3
#       elif AHB_CLOCK > APB_CLOCK_BOUNDARY(4, 6)
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_4
#           define APB_CLOCK_DIV 4
#       elif AHB_CLOCK > APB_CLOCK_BOUNDARY(6, 8)
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_6
#           define APB_CLOCK_DIV 6
#       elif AHB_CLOCK > APB_CLOCK_BOUNDARY(8, 16)
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_8
#           define APB_CLOCK_DIV 8
#       else /* AHB_CLOCK > (APB_SOURCE_CLOCK / 16) or others */
#           define SET_APB_DIV SMU_CLK_SRC_APB_DIV_16
#           define APB_CLOCK_DIV 16
#       endif
#   endif
#endif
#ifndef SET_APB_DIV
#   define SET_APB_DIV SMU_CLK_SRC_APB_DIV_2 /* default */
#   define APB_CLOCK_DIV 2
#   define APB_CLOCK (APB_SOURCE_CLOCK / APB_CLOCK_DIV)
#endif

	/* setup ahb & apb speed */
	WRITE_AOSMU_REG(AOSMU_REG_CLK_SRC,
		    SMU_CLK_SRC_250M | SET_AHB_DIV | SET_APB_DIV);

#ifdef CONFIG_TIMER_READS_ITS_FREQUENCY_AT_RUNTIME
	extern unsigned int z_clock_hw_cycles_per_sec;
	uint32_t root_clock = et171_otp_get_root_clock();

	if (0 == root_clock) {
		root_clock = 205 * 10000000;
	}
	z_clock_hw_cycles_per_sec = root_clock
			      / (AHB_CLOCK_DIV * 2 * APB_CLOCK_DIV);
#endif
}

void soc_early_init_hook(void)
{
#if CONFIG_XIP && CONFIG_ICACHE
	/* Since caching is enabled before z_data_copy(), RAM functions may still be cached
	 * in the d-cache instead of being written to SRAM. In this case, the i-cache will
	 * fetch the wrong content from SRAM. Thus, using "fence.i" to fix it.
	 */
	__asm__ volatile("fence.i" ::: "memory");
#endif

	/* Load and perform analog trimming value from OTP */
	et171_otp_load_analog_config();

	/* Although the root clock configuration is declared in the `clock` node, to avoid
	 * unnecessary impact on the clock configuration due to clock driver initialize
	 * priority settings, the clock configuration is performed by `soc_early_init_hook`.
	 */
	et171_config_soc_clock();

	/* Workaround WFI wakeup issue. AE350_I2C->INTEN = 1;       */
	sys_write32(1, 0xF0A00014U);
}
