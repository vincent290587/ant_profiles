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

#ifndef ANT_FEC_PAGE_16_H__
#define ANT_FEC_PAGE_16_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_fec_page16 Bicycle Power profile page 16
 * @{
 * @ingroup ant_sdk_profiles_fec_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Data structure for Bicycle Power data page 16.
 *
 * @note This structure implements only page 16 specific data.
 */
typedef struct
{
    uint8_t equipment_type;
    uint8_t elapsed_time;
    uint8_t distance_traveled;
    uint16_t speed;
    uint8_t heart_rate;
	uint8_t cap_state;
} ant_fec_page16_data_t;

/**@brief Initialize page 16.
 */
#define DEFAULT_ANT_FEC_PAGE16()                               \
    (ant_fec_page16_data_t)                                    \
    {                                                           \
        .equipment_type                 = 0,                \
        .elapsed_time     = 0,                \
        .distance_traveled  = 0,                \
        .speed                  = 0,                \
        .heart_rate                = 0,                \
		.cap_state                = 0                \
    }

/**@brief Function for encoding page 16.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_fec_page_16_encode(uint8_t                      * p_page_buffer,
                             ant_fec_page16_data_t const * p_page_data);

/**@brief Function for decoding page 16.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_fec_page_16_decode(uint8_t const          * p_page_buffer,
                             ant_fec_page16_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_PAGE_16_H__
/** @} */
