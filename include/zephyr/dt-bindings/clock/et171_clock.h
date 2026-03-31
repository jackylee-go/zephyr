/*
 * Copyright (c 2026 Egis Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ET171 SoC clock control definitions.
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_ET171_CLOCK_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_ET171_CLOCK_H_

#define ET171_CLOCK_CAN         19 /**< CAN peripheral clock */
#define ET171_CLOCK_SPIM3       18 /**< SPI master 3 clock */
#define ET171_CLOCK_SYSRAM3     17 /**< System RAM 3 clock */
#define ET171_CLOCK_SYSRAM2     16 /**< System RAM 2 clock */
#define ET171_CLOCK_SYSRAM      15 /**< System RAM 1 clock */
#define ET171_CLOCK_SPIM2       14 /**< SPI master 2 clock */
#define ET171_CLOCK_SPIM1       13 /**< SPI master 1 clock */
#define ET171_CLOCK_SPIS        12 /**< SPI slave clock */
#define ET171_CLOCK_CRYPTO      11 /**< Crypto IP clock */
#define ET171_CLOCK_DMAC        10 /**< DMA controller clock */
#define ET171_CLOCK_USB2        9  /**< USB2 IP clock */
#define ET171_CLOCK_HWA         8  /**< HWA IP clock */
#define ET171_CLOCK_HWA2        7  /**< HWA2 IP clock */
#define ET171_CLOCK_GPIO        6  /**< GPIO peripheral clock */
#define ET171_CLOCK_PITPWM      5  /**< PIT peripheral clock */
#define ET171_CLOCK_I2C         4  /**< I2C peripheral clock */
#define ET171_CLOCK_UART        3  /**< UART peripheral clock */
#define ET171_CLOCK_OTPC        2  /**< OPT controller clock */
#define ET171_CLOCK_WDT         1  /**< WDT controller clock */
#define ET171_CLOCK_RTC         0  /**< RTC peripheral clock */

#define ET171_CLOCK_AHB         31 /**< AHB clock */
#define ET171_CLOCK_APB         30 /**< APB clock */
#define ET171_CLOCK_CPU         29 /**< CPU clock */

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_ET171_CLOCK_H_ */
