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
#if NRF_MODULE_ENABLED(ANT_COMMON_PAGE_71)

#include <string.h>
#include "ant_common_page_71.h"

#define NRF_LOG_MODULE_NAME ant_common_page_71
#if ANT_COMMON_PAGE_71_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_COMMON_PAGE_71_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_COMMON_PAGE_71_INFO_COLOR
#else // ANT_COMMON_PAGE_71_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_COMMON_PAGE_71_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


/**@brief Function for tracing page 71 data.
 *
 * @param[in]  p_page_data      Pointer to the page 71 data.
 */
static void page71_data_log(volatile ant_common_page71_data_t const * p_page_data)
{
    NRF_LOG_INFO("last_cmd_id:               %u\r\n", p_page_data->last_cmd_id);
    NRF_LOG_INFO("sequence:                  %u\r\n", p_page_data->sequence);
    NRF_LOG_INFO("cmd_status:                %u\r\n\n", p_page_data->cmd_status);
    NRF_LOG_INFO("data1:                     %u\r\n\n", p_page_data->data[0]);
    NRF_LOG_INFO("data2:                     %u\r\n\n", p_page_data->data[1]);
    NRF_LOG_INFO("data3:                     %u\r\n\n", p_page_data->data[2]);
    NRF_LOG_INFO("data4:                     %u\r\n\n", p_page_data->data[3]);
}


void ant_common_page_71_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page71_data_t const * p_page_data)
{
    ant_common_page71_data_layout_t * p_outcoming_data = (ant_common_page71_data_layout_t *)p_page_buffer;

    p_outcoming_data->last_cmd_id = p_page_data->last_cmd_id;
    p_outcoming_data->sequence = p_page_data->sequence;
    p_outcoming_data->cmd_status = p_page_data->cmd_status;
    p_outcoming_data->data[0] = p_page_data->data[0];
    p_outcoming_data->data[1] = p_page_data->data[1];
    p_outcoming_data->data[2] = p_page_data->data[2];
    p_outcoming_data->data[3] = p_page_data->data[3];

    page71_data_log(p_page_data);
}


void ant_common_page_71_decode(uint8_t const                     * p_page_buffer,
                               volatile ant_common_page71_data_t * p_page_data)
{
    ant_common_page71_data_layout_t const * p_incoming_data =
        (ant_common_page71_data_layout_t *)p_page_buffer;

    p_page_data->last_cmd_id = p_incoming_data->last_cmd_id;
    p_page_data->sequence = p_incoming_data->sequence;
    p_page_data->cmd_status = p_incoming_data->cmd_status;
    p_page_data->data[0] = p_incoming_data->data[0];
    p_page_data->data[1] = p_incoming_data->data[1];
    p_page_data->data[2] = p_incoming_data->data[2];
    p_page_data->data[3] = p_incoming_data->data[3];

    page71_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_COMMON_PAGE_71)
