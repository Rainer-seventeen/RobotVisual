/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 20:08:14
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-16 14:40:46
 */

// TODO:来实现判定是不是与上一个图标是同一个目标，并对物体进行标号
#ifndef CONTROL_DEFINE_HPP
#define CONTROL_DEFINE_HPP

#include "detection/yolov8_utils.h"
#include <cmath>

const int MOVE_SPEED = 1000; // 假定的单位时间戳物体运动像素

/*摄像机的参数*/
const int CAMERA_X = 720;
const int CAMERA_Y = 720;

namespace control
{
    bool is_movement(cv::Rect box1, cv::Rect box2);
    bool is_in_middle(cv::Rect box);
    // bool is_one_obj(OutputParams now, OutputParams last); // 判断前后两者是不是同一个东西

} // namespace control

#endif
