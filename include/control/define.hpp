/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 20:08:14
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 20:23:29
 */

// TODO:来实现判定是不是与上一个图标是同一个目标，并对物体进行标号

#include "detection/yolov8_utils.h"

static const int MOVE_SPEED = 1; // 假定的单位时间戳物体运动像素

namespace control
{
    bool is_one_obj(OutputParams now, OutputParams last); // 判断前后两者是不是同一个东西

} // namespace control
