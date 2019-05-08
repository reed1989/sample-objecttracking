/**
*
* Copyright(c)<2018>, <Huawei Technologies Co.,Ltd>
*
* @version 1.0
*
* @date 2019-5-6
*/
#ifndef OBJECT_TRACKING_POST_PROCESS_H_
#define OBJECT_TRACKING_POST_PROCESS_H_
#include "hiaiengine/api.h"
#include "hiaiengine/data_type.h"
#include "hiaiengine/engine.h"
#include "hiaiengine/data_type_reg.h"
#include <map>
#include "object_tracking_params.h"

#define INPUT_SIZE 1
#define OUTPUT_SIZE 1

using hiai::Engine;
using namespace hiai;

class ObjectTrackingPostProcess : public hiai::Engine {
public:
    /**
     * @brief constructor
     */
    ObjectTrackingPostProcess();

    /**
     * @brief
     */
    ~ObjectTrackingPostProcess();

    HIAI_StatusT Init(const hiai::AIConfig& config,
                      const std::vector<hiai::AIModelDescription>& model_desc);

    /**
     * @brief HIAI_DEFINE_PROCESS : Overloading Engine Process processing logic
     * @[in]: Define an input port, an output port
     */
    HIAI_DEFINE_PROCESS(INPUT_SIZE, OUTPUT_SIZE);

};

#endif /* OBJECT_TRACKING_POST_PROCESS_H_ */
