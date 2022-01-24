/*
 * ai_sharp_sensor.c
 *
 *  Created on: 22 sty 2022
 *      Author: piotr
 */

#include "app_x-cube-ai.h"
#include "ai_sharp_sensor.h"

#include "usart.h"
#include "tim.h"
#include "adc.h"
#include <stdbool.h>
#include <stdio.h>

static uint32_t adc_measurement = 0;
volatile uint32_t distance_cm = 0;

volatile _Bool button_is_pushed = false;
volatile _Bool adc_data_is_ready = false;
_Bool gesture_is_detected = false;
int32_t brightness = 0;

void ai_sharp_train_data_collect(void)
{
	uint8_t tx_buffer[TX_BUFFER_SIZE];
	static uint32_t adc_data[DATA_BUFFER_SIZE];
	uint32_t i;
	static uint32_t cnt = 0;
	int32_t size;

	if(true == adc_data_is_ready)
	{
		adc_data_is_ready = false;

		for(i=0; i<(DATA_BUFFER_SIZE-1); i++)
		{
			adc_data[i] = adc_data[i+1];
		}

		adc_data[DATA_BUFFER_SIZE-1] = distance_cm;

		cnt++;

		if(1 == button_is_pushed)
		{
			cnt = DATA_BUFFER_SIZE;
		}

		if(cnt >= DATA_BUFFER_SIZE)
		{
			cnt = 0;

			for(i=0; i<DATA_BUFFER_SIZE; i++ )
			{
			  size = sprintf((char *)tx_buffer, "%d,", (int)adc_data[i]);
			  HAL_UART_Transmit(&huart2, tx_buffer, size, 1);
			}

			if(true == button_is_pushed)
			{
				size = sprintf((char *)tx_buffer, "\n1\n");
				button_is_pushed = false;
			}
			else
			{
				size = sprintf((char *)tx_buffer, "\n0\n");
			}

			HAL_UART_Transmit(&huart2, tx_buffer, size, 1);
		}
	}
}

void LED_brightness_control(void)
{
	static uint32_t time_cnt = 0;

	if(time_cnt == 0)
		time_cnt = HAL_GetTick();

	if((HAL_GetTick() - time_cnt) > 100)
	{
		time_cnt = HAL_GetTick();

		if(distance_cm >= DISTANCE_MAX_VALUE)
		{
			gesture_is_detected = false;
			HAL_GPIO_WritePin(DETECT_LED_GPIO_Port, DETECT_LED_Pin, GPIO_PIN_RESET);
		}

		if(true == gesture_is_detected)
		{
			brightness = _CONVERT_DISTANCE_TO_BRIGHTNESS(distance_cm);

			if(brightness > BRIGHTNESS_MAX)
			{
				brightness = BRIGHTNESS_MAX;
			}
			else if(brightness < BRIGHTNESS_MIN)
			{
				brightness = BRIGHTNESS_MIN;
			}

			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint32_t)brightness);
		}
	}
}

void ADC_start_data_measurement(void)
{
	  HAL_ADC_Start_DMA(&hadc1, &adc_measurement, 1);
	  HAL_TIM_Base_Start(&htim3);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(adc_measurement == 0)
		return;

	distance_cm = CONVERT_ADC_TO_DISTANCE(adc_measurement);

	if(distance_cm > DISTANCE_MAX_VALUE)
	{
		distance_cm = DISTANCE_MAX_VALUE;
	}

	adc_data_is_ready = true;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == B1_Pin)
	{
		button_is_pushed = true;
	}
}
