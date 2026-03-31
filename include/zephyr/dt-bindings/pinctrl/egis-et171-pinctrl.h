/*
 * Copyright (c) 2026 Egis Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ET171 SoC pin control definitions.
 */

#ifndef __EGIS_ET171_PINCTRL_H__
#define __EGIS_ET171_PINCTRL_H__

/**< PINMUX combination macro */
#define ET171_PINMUX(port, offset, fn, pad) \
	(((port) << 24) | ((offset) << 16) | ((fn) << 8) | (pad))

/**< Remapping PIN to PAD */
#define ET171_PINMUX_TO_PADNUM(pinmux) \
	((pinmux) & 0xFF)

/**< MUX GPIOs to PAD */
#define MUX_GPIO_PIN0_PAD10    ET171_PINMUX(0, 20, 0, 10) /**< config GPIO0 to PAD10 */
#define MUX_GPIO_PIN1_PAD11    ET171_PINMUX(0, 22, 0, 11) /**< config GPIO0 to PAD11 */
#define MUX_GPIO_PIN2_PAD12    ET171_PINMUX(0, 24, 0, 12) /**< config GPIO2 to PAD12 */
#define MUX_GPIO_PIN3_PAD6     ET171_PINMUX(0, 12, 1, 6)  /**< config GPIO3 to PAD6 */
#define MUX_GPIO_PIN4_PAD7     ET171_PINMUX(0, 14, 1, 7)  /**< config GPIO4 to PAD7 */
#define MUX_GPIO_PIN5_PAD8     ET171_PINMUX(0, 16, 1, 8)  /**< config GPIO5 to PAD8 */
#define MUX_GPIO_PIN6_PAD9     ET171_PINMUX(0, 18, 1, 9)  /**< config GPIO6 to PAD9 */
#define MUX_GPIO_PIN7_PAD13    ET171_PINMUX(0, 26, 1, 13) /**< config GPIO7 to PAD13 */
#define MUX_GPIO_PIN8_PAD14    ET171_PINMUX(0, 28, 1, 14) /**< config GPIO8 to PAD14 */
#define MUX_GPIO_PIN9_PAD25    ET171_PINMUX(1, 18, 0, 25) /**< config GPIO9 to PAD25 */
#define MUX_GPIO_PIN10_PAD27   ET171_PINMUX(1, 22, 0, 27) /**< config GPIO10 to PAD27 */
#define MUX_GPIO_PIN11_PAD29   ET171_PINMUX(1, 26, 1, 29) /**< config PIN0 to PAD29 */
#define MUX_GPIO_PIN12_PAD5    ET171_PINMUX(0, 10, 3, 5)  /**< config PIN0 to PAD5 */
#define MUX_GPIO_PIN13_PAD21   ET171_PINMUX(1, 10, 1, 21) /**< config PIN0 to PAD21 */
#define MUX_GPIO_PIN14_PAD22   ET171_PINMUX(1, 12, 1, 22) /**< config PIN0 to PAD22 */
#define MUX_GPIO_PIN15_PAD23   ET171_PINMUX(1, 14, 1, 23) /**< config PIN0 to PAD23 */
#define MUX_GPIO_PIN16_PAD24   ET171_PINMUX(1, 16, 1, 24) /**< config PIN0 to PAD24 */

/**< MUX SPIM1 to PAD */
#define MUX_SPIM1_WPN_PAD15    ET171_PINMUX(0, 30, 0, 15) /**< config WPN to PAD15 */
#define MUX_SPIM1_MISO_PAD16   ET171_PINMUX(1, 0, 0, 16)  /**< config MISO to PAD16 */
#define MUX_SPIM1_CSN_PAD17    ET171_PINMUX(1, 2, 0, 17)  /**< config CSN to PAD17 */
#define MUX_SPIM1_HOLDN_PAD18  ET171_PINMUX(1, 4, 0, 18)  /**< config HOLDN to PAD18 */
#define MUX_SPIM1_CK_PAD19     ET171_PINMUX(1, 6, 0, 19)  /**< config CLK to PAD19 */
#define MUX_SPIM1_MOSI_PAD20   ET171_PINMUX(1, 8, 0, 20)  /**< config MOSI to PAD20 */

/**< MUX SPIM2 to PAD */
#define MUX_SPIM2_MISO_PAD26   ET171_PINMUX(1, 20, 0, 26) /**< config MISO to PAD26 */
#define MUX_SPIM2_MOSI_PAD28   ET171_PINMUX(1, 24, 0, 28) /**< config MOSI to PAD28 */
#define MUX_SPIM2_CSN_PAD29    ET171_PINMUX(1, 26, 0, 29) /**< config CSN to PAD29 */
#define MUX_SPIM2_CK_PAD30     ET171_PINMUX(1, 28, 0, 30) /**< config CLK to PAD30 */

/**< MUX SPIM3 to PAD */
#define MUX_SPIM3_HOLDN_PAD0   ET171_PINMUX(0, 0, 0, 0)   /**< config HOLDN to PAD0 */
#define MUX_SPIM3_CK_PAD1      ET171_PINMUX(0, 2, 0, 1)   /**< config CLK to PAD1 */
#define MUX_SPIM3_MOSI_PAD2    ET171_PINMUX(0, 4, 0, 2)   /**< config MOSI to PAD2 */
#define MUX_SPIM3_WPN_PAD3     ET171_PINMUX(0, 6, 0, 3)   /**< config WPN to PAD3 */
#define MUX_SPIM3_MISO_PAD4    ET171_PINMUX(0, 8, 0, 4)   /**< config MISO to PAD4 */
#define MUX_SPIM3_CSN_PAD5     ET171_PINMUX(0, 10, 0, 5)  /**< config CSN to PAD5 */

/**< MUX SPIS to PAD */
#define MUX_SPIS_CK_PAD1       ET171_PINMUX(0, 2, 2, 1)   /**< config CLK to PAD1 */
#define MUX_SPIS_MOSI_PAD2     ET171_PINMUX(0, 4, 2, 2)   /**< config MOSI to PAD2 */
#define MUX_SPIS_MISO_PAD4     ET171_PINMUX(0, 8, 2, 4)   /**< config MISO to PAD4 */
#define MUX_SPIS_CSN_PAD5      ET171_PINMUX(0, 10, 2, 5)  /**< config CSN to PAD5 */

/**< MUX UART to PAD */
#define MUX_UART_RX_PAD1       ET171_PINMUX(0, 2, 1, 1)   /**< config RX to PAD1 */
#define MUX_UART_TX_PAD2       ET171_PINMUX(0, 4, 1, 2)   /**< config TX to PAD2 */
#define MUX_UART_RX_PAD13      ET171_PINMUX(0, 26, 0, 13) /**< config RX to PAD13 */
#define MUX_UART_TX_PAD14      ET171_PINMUX(0, 28, 0, 14) /**< config TX to PAD14 */

/**< MUX JTAG to PAD */
#define MUX_JTAG_TCK_PAD6      ET171_PINMUX(0, 12, 0, 6)  /**< config TCK to PAD6 */
#define MUX_JTAG_TMS_PAD7      ET171_PINMUX(0, 14, 0, 7)  /**< config TMS to PAD7 */
#define MUX_JTAG_TDI_PAD8      ET171_PINMUX(0, 16, 0, 8)  /**< config TDI to PAD8 */
#define MUX_JTAG_TDO_PAD9      ET171_PINMUX(0, 18, 0, 9)  /**< config TDO to PAD9 */

/**< MUX PWM to PAD */
#define MUX_PWM_CH0_PAD13      ET171_PINMUX(0, 26, 3, 13) /**< config CH0 to PAD13 */
#define MUX_PWM_CH1_PAD14      ET171_PINMUX(0, 28, 3, 14) /**< config CH1 to PAD14 */
#define MUX_PWM_CH2_PAD11      ET171_PINMUX(0, 22, 2, 11) /**< config CH2 to PAD11 */
#define MUX_PWM_CH3_PAD12      ET171_PINMUX(0, 24, 2, 12) /**< config CH3 to PAD12 */

/**< MUX CAN to PAD */
#define MUX_CAN_TX_PAD11       ET171_PINMUX(0, 22, 3, 11) /**< config TX to PAD11 */
#define MUX_CAN_RX_PAD12       ET171_PINMUX(0, 24, 3, 12) /**< config RX to PAD12 */
#define MUX_CAN_TX_PAD21       ET171_PINMUX(1, 10, 1, 21) /**< config TX to PAD21 */
#define MUX_CAN_RX_PAD22       ET171_PINMUX(1, 12, 1, 22) /**< config RX to PAD22 */

/**< MUX I2C to PAD */
#define MUX_I2C_SCL_PAD11      ET171_PINMUX(0, 22, 1, 11) /**< config CSL to PAD11 */
#define MUX_I2C_SDA_PAD12      ET171_PINMUX(0, 24, 1, 12) /**< config SDA to PAD12 */
#define MUX_I2C_SCL_PAD13      ET171_PINMUX(0, 26, 2, 13) /**< config SCL to PAD13 */
#define MUX_I2C_SDA_PAD14      ET171_PINMUX(0, 28, 2, 14) /**< config SDA to PAD14 */

/**< MUX LIN to PAD */
#define MUX_LIN_TX_PAD23       ET171_PINMUX(1, 14, 2, 23) /**< config TX to PAD23 */
#define MUX_LIN_RX_PAD24       ET171_PINMUX(1, 16, 2, 24) /**< config RX to PAD24 */

#endif	/* __EGIS_ET171_PINCTRL_H__ */
