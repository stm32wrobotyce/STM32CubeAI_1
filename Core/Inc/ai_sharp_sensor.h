/*
 * ai_sharp_sensor.h
 *
 *  Created on: 22 sty 2022
 *      Author: piotr
 */

#ifndef INC_AI_SHARP_SENSOR_H_
#define INC_AI_SHARP_SENSOR_H_

#define CONVERT_ADC_TO_DISTANCE(adc_val)	((37376UL / adc_val) - 4)

#define DATA_BUFFER_SIZE			64
#define TX_BUFFER_SIZE				30
#define DISTANCE_MAX_VALUE			80

#define NETWORK_INPUT_DATA_SIZE		64
#define NETWORK_OUTPUT_DATA_SIZE	2

#define BASE_DISTANCE_VALUE			10
#define BRIGHTNESS_MAX				100
#define BRIGHTNESS_MIN				0

#define _CONVERT_DISTANCE_TO_BRIGHTNESS(distance)		((distance - BASE_DISTANCE_VALUE) * 2)

void ai_sharp_train_data_collect(void);
void LED_brightness_control(void);

void ADC_start_data_measurement(void);

#endif /* INC_AI_SHARP_SENSOR_H_ */
