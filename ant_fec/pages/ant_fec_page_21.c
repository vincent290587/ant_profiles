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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_FEC)

#include <stdio.h>
#include "ant_fec_page_21.h"
#include "ant_fec_utils.h"

#define NRF_LOG_MODULE_NAME "ANT_FEC_PAGE_21"
#if ANT_FEC_PAGE_21_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_INFO_COLOR
#else // ANT_FEC_PAGE_TORQUE_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_TORQUE_LOG_ENABLED
#include "nrf_log.h"


/**@brief bicycle power page torque data layout structure. */
typedef struct
{
    uint8_t reserved_1;
	uint8_t reserved_2;
	uint8_t reserved_3;
	uint8_t cadence;
    uint8_t inst_power[2];
    uint8_t capabilities;
}ant_fec_page21_data_layout_t;



void ant_fec_page21_log(ant_fec_page21_data_t const * p_page_data)
{
    NRF_LOG_INFO("cadence:                %u\r\n", p_page_data->cadence);
    NRF_LOG_INFO("inst_power:             %u\r\n", p_page_data->inst_power);
}


void ant_fec_page21_encode(uint8_t                           * p_page_buffer,
                                 ant_fec_page21_data_t const * p_page_data)
{
    //ant_fec_page21_data_layout_t * p_outcoming_data = (ant_fec_page21_data_layout_t *)p_page_buffer;

}


void ant_fec_page21_decode(uint8_t const               * p_page_buffer,
                                 ant_fec_page21_data_t * p_page_data)
{
    ant_fec_page21_data_layout_t const * p_incoming_data = (ant_fec_page21_data_layout_t *)p_page_buffer;

    p_page_data->cadence         = p_incoming_data->cadence;
    p_page_data->inst_power      = p_incoming_data->inst_power[0] | (p_incoming_data->inst_power[1] << 8);
    p_page_data->capabilities    = p_incoming_data->capabilities;
	
	ant_fec_page21_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
