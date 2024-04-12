/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 21:37:28
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-12 21:26:40
 */

#ifndef DETECTION_CORE_HPP
#define DETECTION_CORE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

#include <math.h>
#include "detection/yolov8_onnx.h"
#include <time.h>
#include <unistd.h>
// #define  VIDEO_OPENCV //if define, use opencv for video.

namespace detection
{
    void core(); // 外部只需要调用core即可，不需要定义
    std::string get_model_path();
}

#endif