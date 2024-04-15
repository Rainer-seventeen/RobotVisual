/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-07 18:04:46
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-15 20:05:06
 */

#include <iostream>
#include <thread>
#include "detection/detection.hpp"
#include "control/control.hpp"

int main()
{
    std::thread(detection::run).detach();

    std::this_thread::sleep_for(std::chrono::seconds(3)); // 等待检测热身完毕

    std::thread(control::core).join();

    return 0;
}