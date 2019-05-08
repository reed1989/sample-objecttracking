/*
 * object_tracking_inference.h
 *
 *  Created on: May 7, 2019
 *      Author: root
 */

#ifndef OBJECT_TRACKING_INFERENCE_H_
#define OBJECT_TRACKING_INFERENCE_H_
#include "hiaiengine/api.h"
#include "hiaiengine/ai_model_manager.h"
#include "hiaiengine/ai_types.h"
#include "hiaiengine/data_type.h"
#include "hiaiengine/engine.h"
#include "hiaiengine/multitype_queue.h"
#include "hiaiengine/data_type_reg.h"
#include "hiaiengine/ai_tensor.h"
#include "object_tracking_params.h"

#define INPUT_SIZE 2
#define OUTPUT_SIZE 1
using hiai::Engine;

class ObjectTrackingInference : public hiai::Engine {
public:
    ObjectTrackingInference();
    ~ObjectTrackingInference();
    HIAI_StatusT Init(const hiai::AIConfig& config,
                      const std::vector<hiai::AIModelDescription>& model_desc);
    /**
     * @brief HIAI_DEFINE_PROCESS : override Engine Process logic
     * @[in]: define a input port, a output port
     */
    HIAI_DEFINE_PROCESS(INPUT_SIZE, OUTPUT_SIZE);
};



#endif /* OBJECT_TRACKING_INFERENCE_H_ */
