/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */
#ifndef ANT_FEC_UTILS_H__
#define ANT_FEC_UTILS_H__

#include "app_util.h"
#include "nrf_assert.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

uint16_t ant_fec_utils_slope_to_uint16_t(float simulated_grade);

uint8_t ant_fec_utils_rolling_res_to_uint8_t(float simulated_rolling_res);

uint16_t ant_fec_utils_target_power_to_uint16_t(uint16_t simulated_power);

#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_UTILS_H__

