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


#ifndef ANT_FEC_LOCAL_H__
#define ANT_FEC_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_fec.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ant_fec
 * @{
 */

/**@brief Bicycle Power Sensor RX control block. */
typedef struct
{
    uint16_t calib_timeout;
    enum
    {
        FEC_DISP_CALIB_NONE,      ///< Idle state.
        FEC_DISP_CALIB_REQUESTED, ///< Calibration requested.
    } calib_stat;
} ant_fec_disp_cb_t;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_LOCAL_H__
