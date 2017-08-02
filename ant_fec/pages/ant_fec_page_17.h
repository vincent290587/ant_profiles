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

#ifndef ANT_FEC_PAGE_17_H__
#define ANT_FEC_PAGE_17_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_fec_page17 Bicycle Power profile page 17
 * @{
 * @ingroup ant_sdk_profiles_fec_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t reserved_1;
    uint8_t reserved_2;
    uint8_t cycle_length;
    uint8_t incline[2];
    uint8_t resistance_level;
    uint8_t capabilities;
}ant_fec_page17_data_layout_t;

/**@brief Data structure for Bicycle Power data page 17.
 *
 * @note This structure implements only page 17 specific data.
 */
typedef ant_fec_page17_data_layout_t ant_fec_page17_data_t;


/**@brief Function for encoding page 17.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_fec_page_17_encode(uint8_t                      * p_page_buffer,
                             ant_fec_page17_data_t const * p_page_data);

/**@brief Function for decoding page 17.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_fec_page_17_decode(uint8_t const          * p_page_buffer,
                             ant_fec_page17_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_PAGE_17_H__
/** @} */
