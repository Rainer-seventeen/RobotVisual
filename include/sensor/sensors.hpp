/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-07 20:36:14
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-07 20:38:35
 */

#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <opencv2/core.hpp>

struct AutoExposureParam
{
    double min_brightness = 60;
    double max_brightness = 100;
    double step_exposure_us = 200;
    double min_exposure_us = 1000;
    double max_exposure_us = 9000;
};

struct SensorsData
{
    cv::Mat im; // 传感器图像
    std::array<double, 4> q;
    double timestamp; // ms
};

struct SensorParam
{
    cv::Mat K;
    cv::Mat D;
    cv::Mat Tcb;
};

#endif
