#ifndef BatchImageParaWithScale_H_
#define BatchImageParaWithScale_H_

#include "hiaiengine/data_type.h"
#include "hiaiengine/data_type_reg.h"
#include "hiaiengine/status.h"
#include <unistd.h>
#include <sys/stat.h>

using hiai::BatchInfo;
using hiai::IMAGEFORMAT;
using hiai::ImageData;

/**
define error code for HIAI_ENGINE_LOG
**/
#define USE_DEFINE_ERROR 0x6001

enum{
    HIAI_IDE_ERROR_CODE,
    HIAI_IDE_INFO_CODE,
    HIAI_IDE_WARNING_CODE
};

HIAI_DEF_ERROR_CODE(USE_DEFINE_ERROR, HIAI_ERROR, HIAI_IDE_ERROR, \
    "");
HIAI_DEF_ERROR_CODE(USE_DEFINE_ERROR, HIAI_INFO, HIAI_IDE_INFO, \
    "");
HIAI_DEF_ERROR_CODE(USE_DEFINE_ERROR, HIAI_WARNING, HIAI_IDE_WARNING, \
    "");

typedef struct ScaleInfo {
    float scale_width = 1;
    float scale_height = 1;
} ScaleInfoT;
template <class Archive>
void serialize(Archive& ar, ScaleInfoT& data) {
    ar(data.scale_width, data.scale_height);
}

typedef struct ResizeInfo {
    uint32_t resize_width = 0;
    uint32_t resize_height = 0;
} ResizeInfoT;
template <class Archive>
void serialize(Archive& ar, ResizeInfo& data) {
    ar(data.resize_width, data.resize_height);
}

typedef struct CropInfo {
    int point_x = -1;
    int point_y = -1;
    int crop_width = -1;
    int crop_height = -1;
} CropInfoT;
template <class Archive>
void serialize(Archive& ar, CropInfo& data) {
    ar(data.point_x, data.point_y, data.crop_width, data.crop_height);
}



typedef struct NewImagePara {
    hiai::FrameInfo f_info;
    hiai::ImageData<u_int8_t> img;
    ScaleInfoT scale_info;
    ResizeInfo resize_info;
    CropInfo crop_info;
} NewImageParaT;

template <class Archive>
void serialize(Archive& ar, NewImageParaT& data) {
    ar(data.f_info, data.img, data.scale_info,data.resize_info, data.crop_info);
}

typedef struct NewImagePara2 {
    hiai::FrameInfo f_info;
    hiai::ImageData<float> img;
    ScaleInfoT scale_info;
} NewImageParaT2;

template <class Archive>
void serialize(Archive& ar, NewImageParaT2& data) {
    ar(data.f_info, data.img, data.scale_info);
}

typedef struct BatchImageParaWithScale {
    hiai::BatchInfo b_info;
    std::vector<NewImageParaT> v_img;
} BatchImageParaWithScaleT;

template <class Archive>
void serialize(Archive& ar, BatchImageParaWithScaleT& data) {
    ar(data.b_info, data.v_img);
}

struct ImageAll {
    int width_org;
    int height_org;
    int channal_org;
    ImageData<float> image;
};

template <class Archive>
void serialize(Archive& ar, ImageAll& data) {
    ar(data.width_org, data.height_org, data.channal_org, data.image);
}

struct BatchImageParaScale {
    BatchInfo b_info;             
    std::vector<ImageAll> v_img; 
};

template <class Archive>
void serialize(Archive& ar, BatchImageParaScale& data) {
    ar(data.b_info, data.v_img);
}

typedef enum ImageType{
    IMAGE_TYPE_RAW = -1,
    IMAGE_TYPE_NV12 = 0,
    IMAGE_TYPE_JPEG,
    IMAGE_TYPE_PNG,
    IMAGE_TYPE_BMP,
    IMAGE_TYPE_TIFF,
    IMAGE_TYPE_VIDEO = 100
}ImageTypeT;

struct EvbImageInfo{
    bool is_first;
    bool is_last;
    uint32_t batch_size;
    uint32_t batch_index;
    uint32_t max_batch_size;
    uint32_t batch_ID;
    uint32_t frame_ID;
    int format;
    uint32_t width  = 0;
    uint32_t height = 0;
    uint32_t size = 0;
    u_int8_t* pucImageData;
};

const int SEND_DATA_INTERVAL_MS = 200000;
const static mode_t PERMISSION = 0700;
const static mode_t FIlE_PERMISSION = 0600;

//The new version of serialize function
void GetEvbImageInfoSearPtr(void *input_ptr, std::string& ctrl_str, uint8_t*& data_ptr, uint32_t& data_len)
{
    if(input_ptr == nullptr){
        return;
    }
    EvbImageInfo* image_info = (EvbImageInfo*)input_ptr;
    ctrl_str = std::string((char*)input_ptr, sizeof(EvbImageInfo));
    data_ptr = (uint8_t*)image_info->pucImageData;
    data_len = image_info->size;
}

bool isSentinelImage(const std::shared_ptr<BatchImageParaWithScaleT> image_handle){
    if (image_handle && image_handle->b_info.batch_ID == -1){
        return true;
    }
    return false;
}

//The new version of deserialize function
std::shared_ptr<void> GetEvbImageInfoDearPtr(const char* ctrl_ptr, const uint32_t& ctr_len, const uint8_t* data_ptr, const uint32_t& data_len)
{
    if(ctrl_ptr == nullptr){
        return NULL;
    }
    EvbImageInfo* image_info = (EvbImageInfo*)ctrl_ptr;
    std::shared_ptr<BatchImageParaWithScaleT> image_handle = std::make_shared<BatchImageParaWithScaleT>();
    image_handle->b_info.frame_ID.push_back(image_info->frame_ID);
    image_handle->b_info.batch_size = image_info->batch_size;
    image_handle->b_info.max_batch_size = image_info->max_batch_size;
    image_handle->b_info.batch_ID = image_info->batch_ID;
    image_handle->b_info.is_first = image_info->is_first;
    image_handle->b_info.is_last = image_info->is_last;
    if(isSentinelImage(image_handle)){
        return image_handle;
    }
    NewImageParaT imgData;
    imgData.img.format = (IMAGEFORMAT)image_info->format;
    imgData.img.width = image_info->width ;
    imgData.img.height = image_info->height;
    imgData.img.size = image_info->size; // Get image info size;
    imgData.img.data.reset((uint8_t*)data_ptr, hiai::Graph::ReleaseDataBuffer);
    image_handle->v_img.push_back(imgData);
    return std::static_pointer_cast<void>(image_handle);
}
typedef struct Output
{
    int32_t size;
    std::string name;
    std::shared_ptr<u_int8_t> data;
}OutputT;
template<class Archive>
void serialize(Archive& ar, OutputT& data)
{
    ar(data.size);
    ar(data.name);
    if (data.size > 0 && data.data.get() == nullptr)
    {
        data.data.reset(new u_int8_t[data.size]);
    }

    ar(cereal::binary_data(data.data.get(), data.size * sizeof(u_int8_t)));
}


typedef struct EngineTrans
{
    bool status;
    std::string msg;
    hiai::BatchInfo b_info;
    uint32_t size;
    std::vector<OutputT> output_data_vec;
    std::vector<NewImageParaT> v_img;   
}EngineTransT;
template<class Archive>
void serialize(Archive& ar, EngineTransT& data)
{
   ar(data.status, data.msg, data.b_info, data.size, data.output_data_vec, data.v_img);
}

typedef struct {
    std::string tfilename;
    int format;
    int height;
    int width;
}ImageInfor;

/**
* @brief: get the result file name from the image name
* @[in]: imgFullPath: the image file path
* @[in]: postfix: the type of the result file
*/
std::string GenTfileName(std::string imgFullPath, std::string postfix) {
    std::size_t name_cnt = imgFullPath.find_last_of(".");
    std::size_t found = imgFullPath.find_last_of("/\\");
    std::string tfileName = "davinci_" + imgFullPath.substr(found + 1, name_cnt - found - 1) + postfix;
    return tfileName;
}

/**
* @brief: get the image information from the info_file generated by dataset engine
* @[in]: info_file: the info file path
* @[in]: postfix: the type of the result file
*/
std::unordered_map<int, ImageInfor> SetImgPredictionCorrelation(std::string info_file, std::string postfix) {
    std::ifstream fin(info_file.c_str());
    if (!fin) {
        HIAI_ENGINE_LOG(HIAI_IDE_ERROR, "fail to open info file.");
    }
    std::unordered_map<int, ImageInfor> result;
    std::string line_content;

    std::getline(fin, line_content);
    std::string  datasetName;
    int totalFileNum = 0;
    std::stringstream lineStr1(line_content);
    lineStr1 >> datasetName >> totalFileNum;

    int format = -2;
    int fileNumByFormat = 0;
    int count = 0;
    while (count < totalFileNum) {
        std::getline(fin, line_content);
        std::stringstream lineStrFormat0(line_content);
        lineStrFormat0 >> format >> fileNumByFormat;
        count += fileNumByFormat;
        for (int ind = 0; ind < fileNumByFormat; ind++) {
            std::getline(fin, line_content);
            int frame_id;
            std::string img_fullpath;
            int width, height;
            std::stringstream lineStr(line_content);
            lineStr >> frame_id >> img_fullpath >> width >> height;
            ImageInfor img_infor;
            img_infor.tfilename = GenTfileName(img_fullpath, postfix);
            img_infor.height = height;
            img_infor.width = width;
            img_infor.format = format;
            result[frame_id] = img_infor;
        }
    }
    return result;
}

/**
* @brief: get the caffe layer name and index
* @[in]: in_name: the name of tensor
* @[in]: index: the index of output tensor
* @[in]: out_name: the caffe layer name
*/
void GetLayerName(const std::string in_name, std::string& index, std::string& out_name) {
    auto pos = in_name.find_last_of("_");
    index = in_name.substr(pos + 1);
    out_name = in_name.substr(0, pos);
    for (int num_underline = 2; num_underline>0; num_underline--) {
        auto pos_underline = out_name.find_first_of("_");
        out_name = out_name.substr(pos_underline + 1);
    }
}

/**
* @brief: create folder to store the detection results
* the folder name on the host will be "result_files/enginename"
*/
HIAI_StatusT CreateFolder(std::string folderPath, mode_t mode) {
    int folder_exist = access(folderPath.c_str(), W_OK);
    if (-1 == folder_exist)
    {
        if (mkdir(folderPath.c_str(), mode) == -1)
        {
            HIAI_ENGINE_LOG(HIAI_IDE_ERROR, "Create %s failed !", folderPath.c_str());
            return HIAI_ERROR;
        }
    }
    return HIAI_OK;
}

/**
* @brief: get the information file path in the dataset folder
* @[in]: value, path configuration string
* @[return]: string, info file path
*/
std::string GetInfoFilePath(const std::string pathConfig) {
    std::string datainfo_path = pathConfig;
    while (datainfo_path.back() == '/' || datainfo_path.back() == '\\') {
        datainfo_path.pop_back();
    }
    std::size_t tmp_ind = datainfo_path.find_last_of("/\\");
    std::string info_file_ = datainfo_path + "/" + "." + datainfo_path.substr(tmp_ind + 1) + "_data.info";
    HIAI_ENGINE_LOG(HIAI_IDE_INFO, "info file:%s", info_file_.c_str());
    return info_file_;
}
#endif
