/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 20:08:24
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-16 14:12:03
 */
#include "control/define.hpp"

bool control::is_movement(cv::Rect box1, cv::Rect box2)
{
    // 判断两个框是不是在正常运行范围内，这个功能是不是要实现，待定

    int move_x = abs(box1.x - box2.x);
    int move_y = abs(box1.y - box2.y);

    if (move_x * move_x + move_y * move_y <= MOVE_SPEED * MOVE_SPEED)
        return true;
    else
        return false;
}

bool control::is_in_middle(cv::Rect box)
{
    /*判定为图像中间左右15%的区域*/
    const int boundary_x1 = CAMERA_X / 2 - CAMERA_X * 0.15; // 左上
    const int boundary_y1 = CAMERA_Y / 2 - CAMERA_Y * 0.15; // 左下
    const int boundary_x2 = CAMERA_X / 2 + CAMERA_X * 0.15; // 右上
    const int boundary_y2 = CAMERA_Y / 2 + CAMERA_Y * 0.15; // 右下
    const int box_x = (box.x + box.width / 2);
    const int box_y = (box.y + box.height / 2);

    if (box_x > boundary_x1 && box_x < boundary_x2 && box_y > boundary_y1 && box_y < boundary_y2)
        return true;
    else
        return false;
}