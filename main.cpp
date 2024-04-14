/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-07 18:04:46
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 21:53:27
 */

#include <iostream>
#include <thread>
#include "detection/detection.hpp"
#include "control/control.hpp"

int main()
{
    // TODO 如何实现多线程，尚待学习
    std::thread Detection(detection::run);
    std::thread Control(control::core);

    Detection.join();
    Control.join();
    return 0;
}