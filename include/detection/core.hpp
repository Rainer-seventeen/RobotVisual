/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 21:37:28
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-15 19:36:36
 */

#ifndef DETECTION_CORE_HPP
#define DETECTION_CORE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <unistd.h>
#include <umt/umt.hpp>
// #define  VIDEO_OPENCV //if define, use opencv for video.
#include "detection/detection_pack.hpp"
#include "detection/yolov9_onnx.h"
#include <fmt/format.h>
#include <fmt/color.h>
#include <thread>

namespace detection
{
    void core(); // 外部只需要调用core即可，不需要定义
    std::string get_model_path();
    void PrintInfo(const OutputParams oneresult, std::vector<std::string> classNames);
}

#endif