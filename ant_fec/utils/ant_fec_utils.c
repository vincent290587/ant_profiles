#include <stdint.h>
#include "app_util.h"
#include "nrf_assert.h"
#include "ant_fec_pages.h"
#include "nrf.h"



uint16_t ant_fec_utils_slope_to_uint16_t(float simulated_grade) {

	uint16_t res = 0;

	float raw_grade = (simulated_grade + 200)  / ANT_FEC_PAGE51_SLOPE_LSB;

	res = (uint16_t)(raw_grade);

	return res;
}

uint8_t ant_fec_utils_rolling_res_to_uint8_t(float simulated_rolling_res) {

	uint16_t res = 0;

	float raw_res = simulated_rolling_res  / ANT_FEC_PAGE51_ROLL_RES_LSB;

	res = (uint16_t)(raw_res);

	return res;
}


uint16_t ant_fec_utils_target_power_to_uint16_t(uint16_t simulated_power) {

	uint16_t res = simulated_power  / ANT_FEC_PAGE49_TARGET_POWER_LSB;

	return res;
}

/**
 *
 * @param raw_speed
 * @return Speed in hector meters per hour
 */
uint16_t ant_fec_utils_raw_speed_to_uint16_t(uint16_t raw_speed) {

	uint16_t res = raw_speed * 10 * ANT_FEC_PAGE16_SPEED_LSB;

	return res;
}

/**
 *
 * @param raw_time
 * @return Time in seconds
 */
uint16_t ant_fec_utils_raw_time_to_uint16_t(uint16_t raw_time) {

	uint16_t res = raw_time * ANT_FEC_PAGE16_EL_TIME_LSB;

	return res;
}
