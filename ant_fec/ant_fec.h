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

/**
 * @file
 * @defgroup ant_fec Bicycle Power profile
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements the Bicycle Power profile.
 *
 */

 #ifndef ANT_FEC_H__
 #define ANT_FEC_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_parameters.h"
#include "ant_stack_handler_types.h"
#include "ant_channel_config.h"
#include "ant_fec_pages.h"
#include "sdk_errors.h"

#define FEC_DEVICE_TYPE            0x11u               ///< Device type reserved for ANT+ Bicycle Power.
#define FEC_ANTPLUS_RF_FREQ        0x39u               ///< Frequency, decimal 57 (2457 MHz).
#define FEC_MSG_PERIOD             8192u               ///< Message period, decimal 8182 (4 Hz).

#define FEC_EXT_ASSIGN             0x00                ///< ANT ext assign (see Ext. Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
#define FEC_DISP_CHANNEL_TYPE      CHANNEL_TYPE_SLAVE  ///< Display Bicycle Power channel type.

#define FEC_CALIBRATION_TIMOUT_S   150u                  ///< Time-out for responding to calibration callback (s).

/**@brief Initialize an ANT channel configuration structure for the Bicycle Power profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 */
#define FEC_DISP_CHANNEL_CONFIG_DEF(NAME,                              \
                                     CHANNEL_NUMBER,                    \
                                     TRANSMISSION_TYPE,                 \
                                     DEVICE_NUMBER,                     \
                                     NETWORK_NUMBER)                    \
static const ant_channel_config_t   NAME##_channel_fec_disp_config =   \
    {                                                                   \
        .channel_number    = (CHANNEL_NUMBER),                          \
        .channel_type      = FEC_DISP_CHANNEL_TYPE,                    \
        .ext_assign        = FEC_EXT_ASSIGN,                           \
        .rf_freq           = FEC_ANTPLUS_RF_FREQ,                      \
        .transmission_type = (TRANSMISSION_TYPE),                       \
        .device_type       = FEC_DEVICE_TYPE,                          \
        .device_number     = (DEVICE_NUMBER),                           \
        .channel_period    = FEC_MSG_PERIOD,                           \
        .network_number    = (NETWORK_NUMBER),                          \
    }
#define FEC_DISP_CHANNEL_CONFIG(NAME) &NAME##_channel_fec_disp_config

/**@brief Initialize an ANT profile configuration structure for the FEC profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  EVT_HANDLER          Event handler to be called for handling events in the FEC profile.
 */
#define FEC_DISP_PROFILE_CONFIG_DEF(NAME,                              \
                                     EVT_HANDLER)                       \
static ant_fec_disp_cb_t            NAME##_fec_disp_cb;               \
static const ant_fec_disp_config_t  NAME##_profile_fec_disp_config =  \
    {                                                                   \
        .p_cb               = &NAME##_fec_disp_cb,                     \
        .evt_handler        = (EVT_HANDLER),                            \
    }
#define FEC_DISP_PROFILE_CONFIG(NAME) &NAME##_profile_fec_disp_config



/**@brief Bicycle Power page number type. */
typedef enum
{
    ANT_FEC_PAGE_1  = 1,
    ANT_FEC_PAGE_2  = 2,
	ANT_FEC_PAGE_16 = 16, ///< Standard power-only main data page.
    ANT_FEC_PAGE_17 = 17, ///< Standard wheel torque main data page.
    ANT_FEC_PAGE_21 = 21,
    ANT_FEC_PAGE_25 = 25,
    ANT_FEC_PAGE_48 = 48,
    ANT_FEC_PAGE_49 = 49,
    ANT_FEC_PAGE_51 = 51,
    ANT_FEC_PAGE_71 = ANT_COMMON_PAGE_71,
    ANT_FEC_PAGE_80 = ANT_COMMON_PAGE_80,
    ANT_FEC_PAGE_81 = ANT_COMMON_PAGE_81
} ant_fec_page_t;

/**@brief FEC profile event type. */
typedef enum
{
    ANT_FEC_PAGE_1_UPDATED  = ANT_FEC_PAGE_1,
    ANT_FEC_PAGE_2_UPDATED  = ANT_FEC_PAGE_2,
	ANT_FEC_PAGE_16_UPDATED = ANT_FEC_PAGE_16, ///< Data page 16 and speed have been updated (Display) or sent (Sensor).
    ANT_FEC_PAGE_17_UPDATED = ANT_FEC_PAGE_17, ///< Data page 17 and speed have been updated (Display) or sent (Sensor).
    ANT_FEC_PAGE_21_UPDATED = ANT_FEC_PAGE_21,
    ANT_FEC_PAGE_25_UPDATED = ANT_FEC_PAGE_25,
    ANT_FEC_PAGE_48_UPDATED = ANT_FEC_PAGE_48,
    ANT_FEC_PAGE_49_UPDATED = ANT_FEC_PAGE_49,
    ANT_FEC_PAGE_51_UPDATED = ANT_FEC_PAGE_51,
    ANT_FEC_PAGE_71_UPDATED = ANT_FEC_PAGE_71,
    ANT_FEC_PAGE_80_UPDATED = ANT_FEC_PAGE_80, ///< Data page 80 has been updated (Display) or sent (Sensor).
    ANT_FEC_PAGE_81_UPDATED = ANT_FEC_PAGE_81, ///< Data page 81 has been updated (Display) or sent (Sensor).
    ANT_FEC_CALIB_TIMEOUT,                      ///< Request of calibration time-out occurred (Display).
    ANT_FEC_CALIB_REQUEST_TX_FAILED,            ///< Calibration request did not reach the destination (Display).
    ANT_FEC_TX,                                 // TX time
} ant_fec_evt_t;

// Forward declaration of the ant_fec_profile_t type.
typedef struct ant_fec_profile_s ant_fec_profile_t;

/**@brief FEC event handler type. */
typedef void (* ant_fec_evt_handler_t) (ant_fec_profile_t *, ant_fec_evt_t);

/**@brief FEC Sensor calibration request handler type. */
typedef void (* ant_fec_calib_handler_t) (ant_fec_profile_t *, ant_fec_page1_data_t *);

#include "ant_fec_local.h"

#ifdef __cplusplus
extern "C" {
#endif



/**@brief Bicycle Power Display configuration structure. */
typedef struct
{
    ant_fec_disp_cb_t   * p_cb;            ///< Pointer to the data buffer for internal use.
    ant_fec_evt_handler_t evt_handler;     ///< Event handler to be called for handling events in the FEC profile.
} ant_fec_disp_config_t;

/**@brief FEC profile structure. */
struct ant_fec_profile_s
{
    uint8_t                  channel_number; ///< Channel number assigned to the profile.
    ant_fec_disp_cb_t        * p_disp_cb;                              ///< Pointer to internal control block.
    ant_fec_evt_handler_t    evt_handler;    ///< Event handler to be called for handling events in the FEC profile.
	ant_fec_page1_data_t     page_1;
	ant_fec_page2_data_t     page_2;
    ant_fec_page16_data_t    page_16;        ///< Page 16.
    ant_fec_page17_data_t    page_17;        ///< Page 17.
    ant_fec_page21_data_t    page_21;
    ant_fec_page25_data_t    page_25;
    ant_fec_page48_data_t    page_48;
    ant_fec_page49_data_t    page_49;
    ant_fec_page51_data_t    page_51;
    ant_common_page71_data_t page_71;        ///< Page 80.
    ant_common_page80_data_t page_80;        ///< Page 80.
    ant_common_page81_data_t page_81;        ///< Page 81.
};


/**@brief Bicycle power message data layout structure. */
typedef struct
{
    uint8_t page_number;
    uint8_t page_payload[7];
} ant_fec_message_layout_t;

/**@brief Function for initializing the ANT Bicycle Power Display profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_disp_config    Pointer to the Bicycle Power Display configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_fec_disp_init(ant_fec_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_fec_disp_config_t const * p_disp_config);

/**@brief Function for opening the profile instance channel for ANT FEC Display.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_fec_disp_open(ant_fec_profile_t * p_profile);

/** @name Functions: Sensor calibration API
 * @{
 */

/** @brief Function for initializing the response for a calibration request.
 *
 *  This function should be used to signal the status of the calibration procedure to the ANT profile layer .
 *
 *  @param[in] p_profile   Pointer to the profile instance.
 */
void ant_fec_calib_response(ant_fec_profile_t * p_profile);
/** @} */

/**@brief Function for handling the Display ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Bicycle Power Display profile.
 *
 * @param[in]   p_profile       Pointer to the profile instance.
 * @param[in]   p_ant_event     Event received from the ANT stack.
 */
void ant_fec_disp_evt_handler(ant_fec_profile_t * p_profile, ant_evt_t * p_ant_event);

/** @name Functions: Display calibration API
 * @{
 */

/**@brief Function for initializing the calibration request process from the Bicycle Power Display side.
 *
 * @details This function requests a transfer to the Sensor and starts watching for the calibration response.
 * If a calibration response has already been requested, the function ignores the new request and returns NRF_SUCCESS.
 *
 * @param [in]   p_profile       Pointer to the profile instance.
 * @param [in]   p_page_1        Pointer to the prepared page 1.
 *
 * @return Values returned by the @ref sd_ant_acknowledge_message_tx SVC callback.
 */
uint32_t ant_fec_calib_request(ant_fec_profile_t * p_profile, ant_fec_page1_data_t * p_page_1);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_FEC_H__

