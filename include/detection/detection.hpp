/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-07 18:00:17
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-09 10:28:07
 */
#ifndef DETECTION_HPP
#define DETECTION_HPP

#include "opencv2/opencv.hpp"

struct point_box
{
    // 四个坐标点
    cv::Point2f pts[4]; // [pt0, pt1, pt2, pt3]
    float confidence;
};

namespace detection
{
    void run();
}

#endif