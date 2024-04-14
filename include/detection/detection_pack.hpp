/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 21:04:37
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 21:17:03
 */

// 用于隔离所有的结构体，被control函数调用

#ifndef DETECTION_PACK_HPP
#define DETECTION_PACK_HPP

#include <opencv2/opencv.hpp>
#include <chrono>

typedef std::chrono::system_clock::time_point Timestamp; // 时间戳单位

struct OutputParams
{
    int id;                     // 结果类别id
    float confidence;           // 结果置信度
    cv::Rect box;               // 矩形框
    cv::RotatedRect rotatedBox; // obb结果矩形框
    cv::Mat boxMask;            // 矩形框内mask，节省内存空间和加快速度
};

struct Detection_pack
{
    /*打包数据结构，将识别结果、对应的图像、陀螺仪和时间戳对应*/
    std::vector<OutputParams> result;
    Timestamp timestamp;
};

#endif