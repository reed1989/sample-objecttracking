/*
 * object_tracking_inference.cpp
 *
 *  Created on: May 7, 2019
 *      Author: root
 */

#include "object_tracking_inference.h"
#include <hiaiengine/log.h>
#include <hiaiengine/ai_types.h>
#include "hiaiengine/ai_memory.h"
#include <vector>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <algorithm>
#include <iostream>

//const static int IMAGE_INFO_DATA_NUM = 3;
HIAI_REGISTER_DATA_TYPE("EngineTransT", EngineTransT);
HIAI_REGISTER_DATA_TYPE("OutputT", OutputT);
HIAI_REGISTER_DATA_TYPE("ScaleInfoT", ScaleInfoT);
HIAI_REGISTER_DATA_TYPE("NewImageParaT", NewImageParaT);
HIAI_REGISTER_DATA_TYPE("BatchImageParaWithScaleT", BatchImageParaWithScaleT);
HIAI_REGISTER_SERIALIZE_FUNC("EvbImageInfo", EvbImageInfo, GetEvbImageInfoSearPtr, GetEvbImageInfoDearPtr);


ObjectTrackingInference::~ObjectTrackingInference(){

}

HIAI_StatusT ObjectTrackingInference::Init(const hiai::AIConfig& config,const std::vector<hiai::AIModelDescription>& model_desc){

    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingInference] start init!");
    hiai::AIStatus ret = hiai::SUCCESS;
    return ret;
}

/**
* @ingroup hiaiengine
* @brief HIAI_DEFINE_PROCESS : Realize the port input/output processing
* @[in]: Define an input port, an output port,
*        And the Engine is registered, its called "HIAIMultiEngineExample"
*/
HIAI_IMPL_ENGINE_PROCESS("ObjectTrackingInference", ObjectTrackingInference, INPUT_SIZE)
{
    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[MindInferenceEngine_1] start process!");
    hiai::AIStatus ret = hiai::SUCCESS;
    HIAI_StatusT hiai_ret = HIAI_OK;

    return HIAI_OK;

}
