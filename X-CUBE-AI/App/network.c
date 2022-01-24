/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Jan 24 13:32:19 2022
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"




#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "4f5e618f37800993b43b7bc2a011a8b0"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon Jan 24 13:32:19 2022"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)




/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 64, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  dense_55_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  dense_55_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  dense_56_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_56_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  dense_57_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  dense_57_nl_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  dense_55_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1024, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  dense_55_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_56_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_56_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_57_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  dense_57_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_0_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  dense_55_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_55_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  dense_55_nl_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_55_nl_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  dense_56_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_56_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_56_nl_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_56_nl_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  dense_57_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_57_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  dense_57_nl_output, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_57_nl_output_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  dense_55_weights, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 64, 16, 1, 1), AI_STRIDE_INIT(4, 4, 256, 4096, 4096),
  1, &dense_55_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  dense_55_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_55_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  dense_56_weights, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 16, 16, 1, 1), AI_STRIDE_INIT(4, 4, 64, 1024, 1024),
  1, &dense_56_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_56_bias, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_56_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_57_weights, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 16, 1, 1, 1), AI_STRIDE_INIT(4, 4, 64, 64, 64),
  1, &dense_57_weights_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  dense_57_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_57_bias_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_57_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_57_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_57_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_57_nl_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &dense_57_nl_chain,
  NULL, &dense_57_nl_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_57_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_56_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_57_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_57_weights, &dense_57_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_57_layer, 2,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_57_chain,
  NULL, &dense_57_nl_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_56_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_56_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_56_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_56_nl_layer, 1,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_56_nl_chain,
  NULL, &dense_57_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_56_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_55_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_56_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_56_weights, &dense_56_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_56_layer, 1,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_56_chain,
  NULL, &dense_56_nl_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_55_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_55_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_55_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_55_nl_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_55_nl_chain,
  NULL, &dense_56_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_55_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_55_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_55_weights, &dense_55_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_55_layer, 0,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_55_chain,
  NULL, &dense_55_nl_layer, AI_STATIC, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 5316, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 128, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &dense_57_nl_output),
  &dense_55_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)
  AI_UNUSED(net_ctx)

  ai_ptr activations_map[1] = AI_C_ARRAY_INIT;

  if (ai_platform_get_activations_map(activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    dense_55_output_array.data = AI_PTR(activations_map[0] + 0);
    dense_55_output_array.data_start = AI_PTR(activations_map[0] + 0);
    dense_55_nl_output_array.data = AI_PTR(activations_map[0] + 0);
    dense_55_nl_output_array.data_start = AI_PTR(activations_map[0] + 0);
    dense_56_output_array.data = AI_PTR(activations_map[0] + 64);
    dense_56_output_array.data_start = AI_PTR(activations_map[0] + 64);
    dense_56_nl_output_array.data = AI_PTR(activations_map[0] + 0);
    dense_56_nl_output_array.data_start = AI_PTR(activations_map[0] + 0);
    dense_57_output_array.data = AI_PTR(activations_map[0] + 64);
    dense_57_output_array.data_start = AI_PTR(activations_map[0] + 64);
    dense_57_nl_output_array.data = AI_PTR(NULL);
    dense_57_nl_output_array.data_start = AI_PTR(NULL);
    
    return true;
  }
  return false;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)
  AI_UNUSED(net_ctx)

  ai_ptr weights_map[1] = AI_C_ARRAY_INIT;

  if (ai_platform_get_weights_map(weights_map, 1, params)) {
    /* Updating weights with array addresses */
    
    dense_55_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_55_weights_array.data = AI_PTR(weights_map[0] + 0);
    dense_55_weights_array.data_start = AI_PTR(weights_map[0] + 0);
    dense_55_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_55_bias_array.data = AI_PTR(weights_map[0] + 4096);
    dense_55_bias_array.data_start = AI_PTR(weights_map[0] + 4096);
    dense_56_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_56_weights_array.data = AI_PTR(weights_map[0] + 4160);
    dense_56_weights_array.data_start = AI_PTR(weights_map[0] + 4160);
    dense_56_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_56_bias_array.data = AI_PTR(weights_map[0] + 5184);
    dense_56_bias_array.data_start = AI_PTR(weights_map[0] + 5184);
    dense_57_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_57_weights_array.data = AI_PTR(weights_map[0] + 5248);
    dense_57_weights_array.data_start = AI_PTR(weights_map[0] + 5248);
    dense_57_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_57_bias_array.data = AI_PTR(weights_map[0] + 5312);
    dense_57_bias_array.data_start = AI_PTR(weights_map[0] + 5312);
    return true;
  }
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/
AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1371,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1371,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

