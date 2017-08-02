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
#include "ant_fec_page_2.h"

#define NRF_LOG_MODULE_NAME "ANT_FEC_PAGE_2"
#if ANT_FEC_PAGE_2_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_INFO_COLOR
#else // ANT_FEC_PAGE_2_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_2_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@brief bicycle power page 1 data layout structure. */
typedef struct
{
    uint8_t calibration_status; ///< Calibration request type
	uint8_t calibration_conditions;
	uint8_t current_temperature;
	uint8_t target_speed[2];
	uint8_t tgt_spin_down_time[2];
} ant_fec_page2_data_layout_t;


static void page2_data_log(ant_fec_page2_data_t const * p_page_data)
{
    NRF_LOG_INFO("calibration_status:           %u\r\n", p_page_data->calibration_status);
    NRF_LOG_INFO("calibration_conditions:            %u\r\n", p_page_data->calibration_conditions);
	NRF_LOG_INFO("current_temperature:            %u\r\n", p_page_data->current_temperature);
	NRF_LOG_INFO("target_speed:            %u\r\n", p_page_data->target_speed);
	NRF_LOG_INFO("tgt_spin_down_time:            %u\r\n", p_page_data->tgt_spin_down_time);
	
}


void ant_fec_page_2_encode(uint8_t                     * p_page_buffer,
                            ant_fec_page2_data_t const * p_page_data)
{
    ant_fec_page2_data_layout_t * p_outcoming_data = (ant_fec_page2_data_layout_t *)p_page_buffer;

    page2_data_log(p_page_data);

	p_outcoming_data->calibration_status = p_page_data->calibration_status;
	p_outcoming_data->calibration_conditions = p_page_data->calibration_conditions;
	p_outcoming_data->current_temperature = p_page_data->current_temperature;
	p_outcoming_data->target_speed[0] = (uint8_t)(p_page_data->target_speed & 0xFF);
	p_outcoming_data->target_speed[1] = (uint8_t)(p_page_data->target_speed >> 8);
	p_outcoming_data->tgt_spin_down_time[0] = (uint8_t)(p_page_data->tgt_spin_down_time & 0xFF);
	p_outcoming_data->tgt_spin_down_time[1] = (uint8_t)(p_page_data->tgt_spin_down_time >> 8);
    
}


void ant_fec_page_2_decode(uint8_t const         * p_page_buffer,
                            ant_fec_page2_data_t * p_page_data)
{
    ant_fec_page2_data_layout_t const * p_incoming_data = (ant_fec_page2_data_layout_t *)p_page_buffer;

    p_page_data->calibration_status = p_incoming_data->calibration_status;
	p_page_data->calibration_conditions = p_incoming_data->calibration_conditions;
	p_page_data->current_temperature = p_incoming_data->current_temperature;
	p_page_data->target_speed = p_incoming_data->target_speed[0] | (p_incoming_data->target_speed[1] << 8);
	p_page_data->tgt_spin_down_time = p_incoming_data->tgt_spin_down_time[0] | (p_incoming_data->tgt_spin_down_time[1] << 8);

    page2_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
