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

#ifndef ANT_FEC_PAGE49_H__
#define ANT_FEC_PAGE49_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_bicycle_p_page_torque Bicycle Power profile pages 17, 18 (commons)
 * @{
 * @ingroup ant_sdk_profiles_fec_pages
 */

#define ANT_FEC_PAGE49_TARGET_POWER_LSB     (0.25)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Common data structure for Bicycle Power data pages 49
 *
 * @note This structure implements specific data that is common for pages 49
 */
typedef struct
{
	uint16_t target_power;
} ant_fec_page49_data_t;



/**@brief Function for encoding pages 17, 18.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_fec_page49_encode(uint8_t                           * p_page_buffer,
                                 ant_fec_page49_data_t const * p_page_data);

/**@brief Function for decoding pages 17, 18.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_fec_page49_decode(uint8_t const               * p_page_buffer,
                                 ant_fec_page49_data_t * p_page_data);

/**@brief Function for logging pages 17, 18.
 *
 * @param[in] p_page_data      Pointer to the page data.
 */
void ant_fec_page49_log(ant_fec_page49_data_t const * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_PAGE_TORQUE_COMMON_H__
/** @} */
