#ifndef ANT_FEC_PAGE_18_H__
#define ANT_FEC_PAGE_18_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_fec_page18 Bicycle Power profile page 18
 * @{
 * @ingroup ant_sdk_profiles_fec_pages
 */

#include <stdint.h>
#include "ant_fec_page_torque.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Data structure for Bicycle Power data page 18.
 *
 * @note This structure implements only page 18 specific data.
 */
typedef ant_fec_page_torque_data_t ant_fec_page18_data_t;

/**@brief Initialize page 18.
 */
#define DEFAULT_ANT_FEC_PAGE18() (ant_fec_page18_data_t) DEFAULT_ANT_FEC_PAGE_TORQUE(0, 0, 0, 0)

/**@brief Function for encoding page 18.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_fec_page_18_encode(uint8_t                      * p_page_buffer,
                             ant_fec_page18_data_t const * p_page_data);

/**@brief Function for decoding page 18.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_fec_page_18_decode(uint8_t const          * p_page_buffer,
                             ant_fec_page18_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_PAGE_18_H__
/** @} */
