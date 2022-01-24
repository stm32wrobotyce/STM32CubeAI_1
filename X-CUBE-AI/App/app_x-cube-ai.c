
#ifdef __cplusplus
 extern "C" {
#endif
/**
  ******************************************************************************
  * @file           : app_x-cube-ai.c
  * @brief          : AI program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\6.0.0
  */
/* Includes ------------------------------------------------------------------*/
/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"

/* USER CODE BEGIN includes */
#include "ai_sharp_sensor.h"
#include "usart.h"

 extern volatile _Bool adc_data_is_ready;
 extern _Bool gesture_is_detected;
 extern volatile uint32_t distance_cm;
/* USER CODE END includes */
/* Global AI objects */
static ai_handle network = AI_HANDLE_NULL;
static ai_network_report network_info;

/* Global c-array to handle the activations buffer */
AI_ALIGNED(4)
static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];

/*  In the case where "--allocate-inputs" option is used, memory buffer can be
 *  used from the activations buffer. This is not mandatory.
 */
#if !defined(AI_NETWORK_INPUTS_IN_ACTIVATIONS)
/* Allocate data payload for input tensor */
AI_ALIGNED(4)
static ai_u8 in_data_s[AI_NETWORK_IN_1_SIZE_BYTES];
#endif

/*  In the case where "--allocate-outputs" option is used, memory buffer can be
 *  used from the activations buffer. This is no mandatory.
 */
#if !defined(AI_NETWORK_OUTPUTS_IN_ACTIVATIONS)
/* Allocate data payload for the output tensor */
AI_ALIGNED(4)
static ai_u8 out_data_s[AI_NETWORK_OUT_1_SIZE_BYTES];
#endif

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle w_addr, ai_handle act_addr)
{
  ai_error err;

  /* 1 - Create an instance of the model */
  err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_network_create");
    return -1;
  }

  /* 2 - Initialize the instance */
  const ai_network_params params = AI_NETWORK_PARAMS_INIT(
      AI_NETWORK_DATA_WEIGHTS(w_addr),
      AI_NETWORK_DATA_ACTIVATIONS(act_addr) );

  if (!ai_network_init(network, &params)) {
      err = ai_network_get_error(network);
      ai_log_err(err, "ai_network_init");
      return -1;
    }

  /* 3 - Retrieve the network info of the created instance */
  if (!ai_network_get_info(network, &network_info)) {
    err = ai_network_get_error(network);
    ai_log_err(err, "ai_network_get_error");
    ai_network_destroy(network);
    network = AI_HANDLE_NULL;
    return -3;
  }

  return 0;
}

static int ai_run(void *data_in, void *data_out)
{
  ai_i32 batch;

  ai_buffer *ai_input = network_info.inputs;
  ai_buffer *ai_output = network_info.outputs;

  ai_input[0].data = AI_HANDLE_PTR(data_in);
  ai_output[0].data = AI_HANDLE_PTR(data_out);

  batch = ai_network_run(network, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_network_get_error(network),
        "ai_network_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
int acquire_and_process_data(void * data)
{
  return 0;
}

int post_process(void * data)
{
  return 0;
}
/* USER CODE END 2 */

/*************************************************************************
  *
  */
void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(ai_network_data_weights_get(), activations);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
	uint32_t i = 0;
	static uint32_t cnt = 0;

	static float nn_input[NETWORK_INPUT_DATA_SIZE] = { 0 };
	float nn_output;

	if(true == adc_data_is_ready)
	{
		adc_data_is_ready = false;

		cnt++;

		for(i=0; i<(NETWORK_INPUT_DATA_SIZE-1); i++ )
		{
			nn_input[i] = nn_input[i+1];
		}

		nn_input[NETWORK_INPUT_DATA_SIZE-1] = ((float)distance_cm/DISTANCE_MAX_VALUE);

		if(cnt > (NETWORK_INPUT_DATA_SIZE-1))
		{
			ai_run(nn_input, &nn_output);
			cnt = NETWORK_INPUT_DATA_SIZE;

			if (nn_output > 0.7)
			{
				cnt = 0;

				if(false == gesture_is_detected)
				{
					HAL_GPIO_WritePin(DETECT_LED_GPIO_Port, DETECT_LED_Pin, GPIO_PIN_SET);
					gesture_is_detected = true;
				}
			}
		}
	}
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
