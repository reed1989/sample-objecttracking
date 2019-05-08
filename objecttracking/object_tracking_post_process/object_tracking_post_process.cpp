/*
 * object_tracking_post_process.cpp
 *
 *  Created on: May 6, 2019
 *      Author: root
 */
#include "object_tracking_post_process.h"

#include <hiaiengine/log.h>
#include <vector>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sstream>
#include <fcntl.h>

HIAI_REGISTER_DATA_TYPE("EngineTransT", EngineTransT);

HIAI_StatusT ObjectTrackingPostProcess::Init(const hiai::AIConfig& config, const  std::vector<hiai::AIModelDescription>& model_desc)
{
    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingPostProcess] start init!");
    hiai::AIStatus ret = hiai::SUCCESS;

    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingPostProcess] end init!");
    return HIAI_OK;
}

/**
* @brief: send sentinel image to inform the graph to destroy
*/
//HIAI_StatusT ObjectTrackingPostProcess::SendSentinelImage() {
//    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ImageClassificationPostProcess_1] sentinel image, process success!");
//    std::shared_ptr<std::string> result_data(new std::string);
//    HIAI_StatusT hiai_ret = HIAI_OK;
//
//    return hiai_ret;
//}

HIAI_IMPL_ENGINE_PROCESS("object_tracking_post_process", ObjectTrackingPostProcess, INPUT_SIZE)
{
    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingPostProcess] start process!");

    HIAI_StatusT hiai_ret = HIAI_OK;

    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "[ObjectTrackingPostProcess] end process!");

    return HIAI_OK;
}


