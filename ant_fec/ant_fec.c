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

#include "nrf_assert.h"
#include "app_error.h"
#include "ant_interface.h"
#include "ant_fec.h"

#define NRF_LOG_MODULE_NAME "ANT_FEC"
#if ANT_FEC_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_INFO_COLOR
#else // ANT_FEC_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_LOG_ENABLED
#include "nrf_log.h"

#define FEC_CALIB_INT_TIMEOUT ((ANT_CLOCK_FREQUENCY * FEC_CALIBRATION_TIMOUT_S) / FEC_MSG_PERIOD) // calibration timeout in ant message period's unit




typedef enum {
	FEC_STATE_INIT,
	FEC_STATE_CAL,
	FEC_STATE_CST_PW,
	FEC_STATE_TRACK
} fec_state;

static fec_state m_fec_state = FEC_STATE_INIT;


/**@brief Function for initializing the ANT Bicycle Power Profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
static ret_code_t ant_fec_init(ant_fec_profile_t         * p_profile,
                                ant_channel_config_t const * p_channel_config)
{
    p_profile->channel_number = p_channel_config->channel_number;

    //p_profile->page_16 = DEFAULT_ANT_FEC_PAGE16();
    //p_profile->page_17 = DEFAULT_ANT_FEC_PAGE17();
    //p_profile->page_21 = DEFAULT_ANT_FEC_PAGE21();
    //p_profile->page_48 = DEFAULT_ANT_FEC_PAGE21();
    //p_profile->page_49 = DEFAULT_ANT_FEC_PAGE21();
    //p_profile->page_51 = DEFAULT_ANT_FEC_PAGE21();
    p_profile->page_80 = DEFAULT_ANT_COMMON_page80();
    p_profile->page_81 = DEFAULT_ANT_COMMON_page81();

    NRF_LOG_INFO("ANT FEC channel %u init\r\n", p_profile->channel_number);
    return ant_channel_init(p_channel_config);
}


ret_code_t ant_fec_disp_init(ant_fec_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_fec_disp_config_t const * p_disp_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_disp_config != NULL);
    ASSERT(p_disp_config->evt_handler != NULL);
    ASSERT(p_disp_config->p_cb != NULL);

    p_profile->evt_handler   = p_disp_config->evt_handler;
    p_profile->p_disp_cb = p_disp_config->p_cb;

    p_profile->p_disp_cb ->calib_timeout = 0;
    p_profile->p_disp_cb ->calib_stat    = FEC_DISP_CALIB_NONE;

    return ant_fec_init(p_profile, p_channel_config);
}


ret_code_t ant_fec_disp_open(ant_fec_profile_t * p_profile)
{
    NRF_LOG_INFO("ANT FEC %u open\r\n", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}




/**@brief Function for decoding messages received by Bicycle Power display message.
 *
 * @note Assume to be call each time when Rx window will occur.
 */
static void disp_message_decode(ant_fec_profile_t * p_profile, uint8_t * p_message_payload)
{
    const ant_fec_message_layout_t * p_fec_message_payload = (ant_fec_message_layout_t *)p_message_payload;

    NRF_LOG_INFO("FEC rx page: %u\r\n", p_fec_message_payload->page_number);

    switch (p_fec_message_payload->page_number)
    {
        case ANT_FEC_PAGE_1:
            ant_fec_page_1_decode(p_fec_message_payload->page_payload, &(p_profile->page_1));
            break;

        case ANT_FEC_PAGE_2:
            ant_fec_page_2_decode(p_fec_message_payload->page_payload, &(p_profile->page_2));
            break;

        case ANT_FEC_PAGE_16:
            ant_fec_page_16_decode(p_fec_message_payload->page_payload, &(p_profile->page_16));
            break;

        case ANT_FEC_PAGE_17:
            ant_fec_page_17_decode(p_fec_message_payload->page_payload, &(p_profile->page_17));
            break;

        case ANT_FEC_PAGE_21:
            ant_fec_page21_decode(p_fec_message_payload->page_payload, &(p_profile->page_21));
            break;

        case ANT_FEC_PAGE_25:
            ant_fec_page25_decode(p_fec_message_payload->page_payload, &(p_profile->page_25));
            break;

        case ANT_FEC_PAGE_48:
            ant_fec_page48_decode(p_fec_message_payload->page_payload, &(p_profile->page_48));
            break;

        case ANT_FEC_PAGE_49:
            ant_fec_page49_decode(p_fec_message_payload->page_payload, &(p_profile->page_49));
            break;

        case ANT_FEC_PAGE_51:
            ant_fec_page51_decode(p_fec_message_payload->page_payload, &(p_profile->page_51));
            break;

        case ANT_COMMON_PAGE_71:
            ant_common_page_71_decode(p_fec_message_payload->page_payload, &(p_profile->page_71));
            break;

        case ANT_COMMON_PAGE_80:
            ant_common_page_80_decode(p_fec_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_COMMON_PAGE_81:
            ant_common_page_81_decode(p_fec_message_payload->page_payload, &(p_profile->page_81));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_fec_evt_t)p_fec_message_payload->page_number);
}


ret_code_t ant_fec_calib_request(ant_fec_profile_t * p_profile, ant_fec_page1_data_t * p_page_1)
{
    ant_fec_message_layout_t fec_message_payload;

    if (p_profile->p_disp_cb->calib_stat == FEC_DISP_CALIB_REQUESTED)
    {
        return NRF_SUCCESS; // calibration in progress, so omit this request
    }

	// TODO
    fec_message_payload.page_number = ANT_FEC_PAGE_1;
	
    ant_fec_page_1_encode(fec_message_payload.page_payload, p_page_1);

    uint32_t err_code = sd_ant_acknowledge_message_tx(p_profile->channel_number,
                                                      sizeof (fec_message_payload),
                                                      (uint8_t *) &fec_message_payload);

    if (err_code == NRF_SUCCESS)
    {
        p_profile->p_disp_cb->calib_timeout = FEC_CALIB_INT_TIMEOUT; // initialize on calibration's time-out
        p_profile->p_disp_cb->calib_stat    = FEC_DISP_CALIB_REQUESTED;
        NRF_LOG_INFO("Start calibration process\r\n");
		m_fec_state = FEC_STATE_CAL;
    }
    return err_code;
}



/**@brief Function for handling calibration events.
 */
static void service_calib(ant_fec_profile_t * p_profile, uint8_t event)
{
    ant_fec_evt_t       fec_event;

    if (p_profile->p_disp_cb->calib_stat == FEC_DISP_CALIB_REQUESTED)
    {
        switch (event)
        {
            case EVENT_RX:
            /* fall through */
            case EVENT_RX_FAIL:

                if (p_profile->p_disp_cb->calib_timeout-- == 0)
                {
                    fec_event = ANT_FEC_CALIB_TIMEOUT;
                    break;
                }
                else
                {
                    return;
                }

            case EVENT_TRANSFER_TX_FAILED:
                fec_event = ANT_FEC_CALIB_REQUEST_TX_FAILED;
                break;

            case EVENT_RX_SEARCH_TIMEOUT:
                fec_event = ANT_FEC_CALIB_TIMEOUT;
                break;

            default:
                return;
        }

        NRF_LOG_INFO("End calibration process\r\n");
        p_profile->p_disp_cb->calib_stat = FEC_DISP_CALIB_NONE;

        p_profile->evt_handler(p_profile, fec_event);
    }
}



void ant_fec_disp_evt_handler(ant_fec_profile_t * p_profile, ant_evt_t * p_ant_event)
{
    if (p_ant_event->channel == p_profile->channel_number)
    {
        ANT_MESSAGE * p_message = (ANT_MESSAGE *)p_ant_event->msg.evt_buffer;

        switch (p_ant_event->event)
        {
            case EVENT_RX:

                if (p_message->ANT_MESSAGE_ucMesgID == MESG_BROADCAST_DATA_ID
                    || p_message->ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID
                    || p_message->ANT_MESSAGE_ucMesgID == MESG_BURST_DATA_ID)
                {
                    disp_message_decode(p_profile, p_message->ANT_MESSAGE_aucPayload);
                }
                break;
				
			case EVENT_TX:

				if (p_profile->p_disp_cb->calib_stat == FEC_DISP_CALIB_NONE)
				{
					p_profile->evt_handler(p_profile, ANT_FEC_TX);
				}


			break;

            default:
                break;
        }
        service_calib(p_profile, p_ant_event->event);
    }
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
