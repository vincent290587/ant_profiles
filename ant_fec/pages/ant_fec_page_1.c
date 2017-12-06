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

#include <string.h>
#include "ant_fec_page_1.h"

#define NRF_LOG_MODULE_NAME "ANT_FEC_PAGE_1"
#if ANT_FEC_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_PAGE_1_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_PAGE_1_INFO_COLOR
#else // ANT_FEC_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_1_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@brief bicycle power page 1 data layout structure. */
typedef struct
{
    uint8_t calibration_req_rep; ///< Calibration request type
	uint8_t reserved_1;
	uint8_t temperature;
	uint8_t zero_offset[2];
	uint8_t spin_down_time[2];
} ant_fec_page1_data_layout_t;


static void page1_data_log(ant_fec_page1_data_t const * p_page_data)
{
    NRF_LOG_INFO("calibration_req_rep:           %u\r\n", p_page_data->calibration_req_rep);
    NRF_LOG_INFO("temperature:            %u\r\n", p_page_data->temperature);
	NRF_LOG_INFO("zero_offset:            %u\r\n", p_page_data->zero_offset);
	NRF_LOG_INFO("spin_down_time:            %u\r\n", p_page_data->spin_down_time);
	
}


void ant_fec_page_1_encode(uint8_t                     * p_page_buffer,
                            ant_fec_page1_data_t const * p_page_data)
{
    ant_fec_page1_data_layout_t * p_outcoming_data = (ant_fec_page1_data_layout_t *)p_page_buffer;

    page1_data_log(p_page_data);

	p_outcoming_data->calibration_req_rep = p_page_data->calibration_req_rep;
	p_outcoming_data->temperature = p_page_data->temperature;
	p_outcoming_data->zero_offset[0] = (uint8_t)(p_page_data->zero_offset & 0xFF);
	p_outcoming_data->zero_offset[1] = (uint8_t)(p_page_data->zero_offset >> 8);
	p_outcoming_data->spin_down_time[0] = (uint8_t)(p_page_data->spin_down_time & 0xFF);
	p_outcoming_data->spin_down_time[1] = (uint8_t)(p_page_data->spin_down_time >> 8);
    
}


void ant_fec_page_1_decode(uint8_t const         * p_page_buffer,
                            ant_fec_page1_data_t * p_page_data)
{
    ant_fec_page1_data_layout_t const * p_incoming_data =
        (ant_fec_page1_data_layout_t *)p_page_buffer;

    p_page_data->calibration_req_rep = p_incoming_data->calibration_req_rep;
	p_page_data->temperature = p_incoming_data->temperature;
	p_page_data->zero_offset = p_incoming_data->zero_offset[0] | (p_incoming_data->zero_offset[1] << 8);
	p_page_data->spin_down_time = p_incoming_data->spin_down_time[0] | (p_incoming_data->spin_down_time[1] << 8);

    page1_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
