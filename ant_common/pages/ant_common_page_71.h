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

#ifndef ANT_COMMON_PAGE_71_H__
#define ANT_COMMON_PAGE_71_H__

/** @file
 *
 * @defgroup ant_common_page_71 ANT+ common page 71
 * @{
 * @ingroup ant_sdk_common_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_COMMON_PAGE_71              (71)        ///< @brief ID value of common page 70.

/**@brief ant+ common page 71 data layout structure. */
typedef struct
{
    uint8_t last_cmd_id;
    uint8_t sequence;
    uint8_t cmd_status;
    uint8_t data[4];
}ant_common_page71_data_layout_t;


/**@brief Data structure for ANT+ common data page 71.
 */
typedef ant_common_page71_data_layout_t ant_common_page71_data_t;


/**@brief Function for encoding page 71.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_common_page_71_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page71_data_t const * p_page_data);

/**@brief Function for decoding page 71.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_common_page_71_decode(uint8_t const                     * p_page_buffer,
                               volatile ant_common_page71_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_COMMON_PAGE_71_H__
/** @} */
