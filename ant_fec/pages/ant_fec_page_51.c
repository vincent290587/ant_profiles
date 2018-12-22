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
#include "ant_fec_page_51.h"
#include "ant_fec_utils.h"

#define NRF_LOG_MODULE_NAME ant_fec_p51
#if ANT_FEC_PAGE_51_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_INFO_COLOR
#else // ANT_FEC_PAGE_TORQUE_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_PAGE_TORQUE_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


/**@brief bicycle power page torque data layout structure. */
typedef struct
{
    uint8_t reserved_1;
	uint8_t reserved_2;
	uint8_t reserved_3;
	uint8_t reserved_4;
    uint8_t grade_slope[2];
	uint8_t roll_res;
}ant_fec_page51_data_layout_t;



void ant_fec_page51_log(ant_fec_page51_data_t const * p_page_data)
{
    NRF_LOG_INFO("grade_slope:                    %u", p_page_data->grade_slope);
	NRF_LOG_INFO("roll_res:                       %u", p_page_data->roll_res);
}


void ant_fec_page51_encode(uint8_t                           * p_page_buffer,
                                 ant_fec_page51_data_t const * p_page_data)
{
    ant_fec_page51_data_layout_t * p_outcoming_data = (ant_fec_page51_data_layout_t *)p_page_buffer;
	
    p_outcoming_data->reserved_1 = 0xFF;
    p_outcoming_data->reserved_2 = 0xFF;
    p_outcoming_data->reserved_3 = 0xFF;
    p_outcoming_data->reserved_4 = 0xFF;
	p_outcoming_data->grade_slope[0] = (uint8_t)(p_page_data->grade_slope & 0xFF);
	p_outcoming_data->grade_slope[1] = (uint8_t)((p_page_data->grade_slope & 0xFF00) >> 8);
	p_outcoming_data->roll_res = p_page_data->roll_res;
}


void ant_fec_page51_decode(uint8_t const               * p_page_buffer,
                                 ant_fec_page51_data_t * p_page_data)
{
    ant_fec_page51_data_layout_t const * p_incoming_data = (ant_fec_page51_data_layout_t *)p_page_buffer;

    p_page_data->grade_slope         = p_incoming_data->grade_slope[0] | (p_incoming_data->grade_slope[1] << 8) ;
	p_page_data->roll_res            = p_incoming_data->roll_res;
	
	ant_fec_page51_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
