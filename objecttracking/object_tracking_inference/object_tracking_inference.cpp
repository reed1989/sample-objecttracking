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


//ObjectTrackingInference::~ObjectTrackingInference(){
//
//}

HIAI_StatusT ObjectTrackingInference::Init(const hiai::AIConfig& config,const std::vector<hiai::AIModelDescription>& model_desc){

    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingInference] start init!");
    hiai::AIStatus ret = hiai::SUCCESS;

    return HIAI_OK;
}


//HIAI_StatusT CropTargetImage(const ImageData<u_int8_t> src_image, )

/**
* @ingroup hiaiengine
* @brief HIAI_DEFINE_PROCESS : Realize the port input/output processing
* @[in]: Define an input port, an output port,
*        And the Engine is registered, its called "HIAIMultiEngineExample"
*/
HIAI_IMPL_ENGINE_PROCESS("object_tracking_inference", ObjectTrackingInference, INPUT_SIZE)
{
    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingInference] start process!");
    hiai::AIStatus ret = hiai::SUCCESS;
    HIAI_StatusT hiai_ret = HIAI_OK;
    if (arg0 == nullptr) {
        HIAI_ENGINE_LOG(HIAI_ENGINE_RUN_ARGS_NOT_RIGHT,
                        "Failed to process invalid message.");
        return HIAI_ERROR;
    }

    std::shared_ptr<BatchImageParaWithScaleT> image_handle =
            std::static_pointer_cast<BatchImageParaWithScaleT>(arg0);

    // check this bath is the first batch or not
    if (image_handle->b_info.is_first){
        HIAI_ENGINE_LOG(HIAI_IDE_INFO, "This batch is the first batch");
        ImageData<u_int8_t> croped_image;
        //HIAI_StatusT crop_ret =

    }

    for (uint32_t i = 0; i < image_handle->b_info.batch_size; i++) {
        HIAI_ENGINE_LOG(HIAI_IDE_INFO, "Start to deal with the image %d",
                        image_handle->b_info.batch_ID);

    }



    return HIAI_OK;

}
