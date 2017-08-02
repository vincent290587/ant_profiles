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
#include "ant_fec_page_25.h"
#include "ant_fec_utils.h"

#define NRF_LOG_MODULE_NAME "ANT_FEC_PAGE_25"
#if ANT_FEC_PAGE_25_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_INFO_COLOR
#else // ANT_FEC_PAGE_TORQUE_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_TORQUE_LOG_ENABLED
#include "nrf_log.h"


/**@brief bicycle power page torque data layout structure. */
typedef struct
{
    uint8_t event_count;
	uint8_t inst_cad;
    uint8_t acc_power[2];
    uint8_t inst_power_lsb;
    uint8_t inst_power_msb_status;
    uint8_t flags;
}ant_fec_page25_data_layout_t;



void ant_fec_page25_log(ant_fec_page25_data_t const * p_page_data)
{
    NRF_LOG_INFO("event_count:           %u\r\n", p_page_data->event_count);
	NRF_LOG_INFO("inst_cad:              %u\r\n", p_page_data->inst_cad);
	NRF_LOG_INFO("acc_power:             %u\r\n", p_page_data->acc_power);
    NRF_LOG_INFO("inst_power:            %u\r\n", p_page_data->inst_power);
	NRF_LOG_INFO("status:                %u\r\n", p_page_data->status);
    NRF_LOG_INFO("flags:                 %u\r\n", p_page_data->flags);
}


void ant_fec_page25_encode(uint8_t                           * p_page_buffer,
                                 ant_fec_page25_data_t const * p_page_data)
{
    //ant_fec_page25_data_layout_t * p_outcoming_data = (ant_fec_page25_data_layout_t *)p_page_buffer;

}


void ant_fec_page25_decode(uint8_t const               * p_page_buffer,
                                 ant_fec_page25_data_t * p_page_data)
{
    ant_fec_page25_data_layout_t const * p_incoming_data = (ant_fec_page25_data_layout_t *)p_page_buffer;

    p_page_data->event_count    = p_incoming_data->event_count;
	p_page_data->inst_cad       = p_incoming_data->inst_cad;
    p_page_data->acc_power      = p_incoming_data->acc_power[0] | (p_incoming_data->acc_power[1] << 8);
    p_page_data->inst_power     = p_incoming_data->inst_power_lsb | ((p_incoming_data->inst_power_msb_status & 0b00001111) << 8);
	p_page_data->status         = (p_incoming_data->inst_power_msb_status & 0b11110000) >> 4;
	p_page_data->flags          = p_incoming_data->flags;
	
	ant_fec_page25_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
