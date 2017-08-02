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

#include "ant_fec_page_17.h"

#define NRF_LOG_MODULE_NAME "ANT_FEC_PAGE_17"
#if ANT_FEC_PAGE_17_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_PAGE_17_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_PAGE_17_INFO_COLOR
#else // ANT_FEC_PAGE_17_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_17_LOG_ENABLED
#include "nrf_log.h"



static void page17_data_log(ant_fec_page17_data_t const * p_page_data)
{
   	NRF_LOG_INFO("cycle_length:        %u\r\n", p_page_data->cycle_length);
	NRF_LOG_INFO("incline_LSB:             %u\r\n", p_page_data->incline[0]);
	NRF_LOG_INFO("incline_MSB:             %u\r\n", p_page_data->incline[1]);
	NRF_LOG_INFO("resistance_level:            %u\r\n", p_page_data->resistance_level);
	NRF_LOG_INFO("capabilities:             %u\r\n", p_page_data->capabilities);
}


void ant_fec_page_17_encode(uint8_t                      * p_page_buffer,
                             ant_fec_page17_data_t const * p_page_data)
{
    //ant_fec_page17_data_layout_t * p_outcoming_data = (ant_fec_page17_data_layout_t *)p_page_buffer;
    //page17_data_log(p_page_data);
}


void ant_fec_page_17_decode(uint8_t const          * p_page_buffer,
                             ant_fec_page17_data_t * p_page_data)
{
	ant_fec_page17_data_t const * p_incoming_data = (ant_fec_page17_data_t *)p_page_buffer;

    p_page_data->reserved_1         = p_incoming_data->reserved_1;
    p_page_data->reserved_2         = p_incoming_data->reserved_2;
    p_page_data->cycle_length       = p_incoming_data->cycle_length;
    p_page_data->incline[0]         = p_incoming_data->incline[0];
    p_page_data->incline[1]         = p_incoming_data->incline[1];
    p_page_data->resistance_level   = p_incoming_data->resistance_level;
    p_page_data->capabilities       = p_incoming_data->capabilities;
	
    page17_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
