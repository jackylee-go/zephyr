/*
 * Copyright (c) 2026 Egis Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SOC_EGIS_ET171_OTP_H__
#define __SOC_EGIS_ET171_OTP_H__

#include <stdint.h>

/**
 *  \brief       Load OTP analog config options to AOSMU registers
 *               It won't read OTP again.
 *  \return      none
 */
void et171_otp_load_analog_config(void);

/**
 *  \brief       Get root clock from OTP
 *  \returns     none
 */
uint32_t et171_otp_get_root_clock(void);

/**
 *  \brief       Get CP UID from OTP shadow ram
 *               It won't read OTP again
 *  \param[out]  uid  output first 16 bytes data in OTP
 *  \return      none
 */
void et171_otp_get_uid(uint8_t uid[16]);



#endif  /* __SOC_EGIS_ET171_OTP_H__ */
