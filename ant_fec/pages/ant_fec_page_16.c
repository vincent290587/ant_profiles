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

#include "ant_fec_page_16.h"

#define NRF_LOG_MODULE_NAME ant_fec_p16
#if ANT_FEC_PAGE_16_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_PAGE_16_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_PAGE_16_INFO_COLOR
#else // ANT_FEC_PAGE_16_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_16_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief bicycle power page 16 data layout structure. */
typedef struct
{
    uint8_t equipment_type;
    uint8_t elapsed_time;
    uint8_t distance_traveled;
    uint8_t speed[2];
    uint8_t heart_rate;
	uint8_t cap_state;
}ant_fec_page16_data_layout_t;


static void page16_data_log(ant_fec_page16_data_t const * p_page_data)
{
	NRF_LOG_INFO("equipment_type:        %u\r\n", p_page_data->equipment_type);
	NRF_LOG_INFO("elapsed_time:          %u\r\n", p_page_data->elapsed_time);
	NRF_LOG_INFO("distance_traveled:     %u\r\n", p_page_data->distance_traveled);
	NRF_LOG_INFO("speed:                 %u\r\n", p_page_data->speed);
	NRF_LOG_INFO("heart_rate:            %u\r\n", p_page_data->heart_rate);
	NRF_LOG_INFO("cap_state:             %u\r\n", p_page_data->cap_state);
}


void ant_fec_page_16_encode(uint8_t                      * p_page_buffer,
                             ant_fec_page16_data_t const * p_page_data)
{
/* 
    ant_fec_page16_data_layout_t * p_outcoming_data = (ant_fec_page16_data_layout_t *)p_page_buffer;

    p_outcoming_data->update_event_count    = p_page_data->update_event_count;
    p_outcoming_data->pedal_power           = p_page_data->pedal_power.byte;

    UNUSED_PARAMETER(uint16_encode(p_page_data->accumulated_power,
                                   p_outcoming_data->accumulated_power));
    UNUSED_PARAMETER(uint16_encode(p_page_data->instantaneous_power,
                                   p_outcoming_data->instantaneous_power));
*/
    page16_data_log(p_page_data);
}


void ant_fec_page_16_decode(uint8_t const          * p_page_buffer,
                             ant_fec_page16_data_t * p_page_data)
{
    ant_fec_page16_data_layout_t const * p_incoming_data = (ant_fec_page16_data_layout_t *)p_page_buffer;

    p_page_data->equipment_type    = p_incoming_data->equipment_type;
    p_page_data->elapsed_time      = p_incoming_data->elapsed_time;
    p_page_data->distance_traveled = p_incoming_data->distance_traveled;
    p_page_data->speed             = p_incoming_data->speed[0] | (p_incoming_data->speed[1] << 8);
    p_page_data->heart_rate        = p_incoming_data->heart_rate;
    p_page_data->cap_state         = p_incoming_data->cap_state;

    page16_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
