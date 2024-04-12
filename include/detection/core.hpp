/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 21:37:28
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-12 22:34:59
 */

#ifndef DETECTION_CORE_HPP
#define DETECTION_CORE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

#include <math.h>
#include <chrono>
#include <unistd.h>
#include <umt/umt.hpp>
// #define  VIDEO_OPENCV //if define, use opencv for video.
#include "detection/yolov8_onnx.h"
#include <fmt/format.h>
#include <fmt/color.h>

typedef std::chrono::system_clock::time_point Timestamp; // 时间戳单位
namespace detection
{
    void core(); // 外部只需要调用core即可，不需要定义
    std::string get_model_path();
}

struct Detection_pack
{
    /*打包数据结构，将识别结果、对应的图像、陀螺仪和时间戳对应*/
    std::vector<OutputParams> result;
    Timestamp timestamp;
};

#endif