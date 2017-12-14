#include <stdint.h>
#include "app_util.h"
#include "nrf_assert.h"
#include "ant_fec_pages.h"
#include "ant_fec_utils.h"
#include "nrf.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

uint16_t ant_fec_utils_slope_to_uint16_t(float simulated_grade) {

	float raw_grade = (simulated_grade + 200)  / ANT_FEC_PAGE51_SLOPE_LSB;

	return raw_grade;
}

uint8_t ant_fec_utils_rolling_res_to_uint8_t(float simulated_rolling_res) {

	uint8_t res = 0;

	float raw_res = simulated_rolling_res  / ANT_FEC_PAGE51_ROLL_RES_LSB;

	res = (uint8_t)(raw_res);

	return res;
}


uint16_t ant_fec_utils_target_power_to_uint16_t(uint16_t simulated_power) {

	float res = simulated_power  / ANT_FEC_PAGE49_TARGET_POWER_LSB;

	return res;
}

/**
 *
 * @param raw_speed
 * @return Speed in hecto meters per hour
 */
uint16_t ant_fec_utils_raw_speed_to_uint16_t(uint16_t raw_speed) {

	float temp = (float)raw_speed * ANT_FEC_PAGE16_SPEED_LSB + 0.5;

	return temp;
}

/**
 *
 * @param raw_time
 * @return Time in seconds
 */
uint16_t ant_fec_utils_raw_time_to_uint16_t(uint16_t raw_time) {

	float temp = (float)raw_time * ANT_FEC_PAGE16_EL_TIME_LSB + 0.5;

	return temp;
}
