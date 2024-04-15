/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 20:06:04
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-15 20:28:17
 */

#include "control/control.hpp"

void control::core()
{
    std::cout << "Task: Control Model Opened!" << std::endl;
    // 考虑将数据的输出放到这里来（已经完成）
    // 先sub一下两个数据

    while (true)
    {
        // std::cout << "AAA" << std::endl; DEBUG

        umt::Subscriber<Detection_pack> detections_sub("detections_pack"); // 订阅传感器信息
        // std::cout << "BBB" << std::endl; DEBUG

        const auto &[result, timestamp] = detections_sub.pop(); // 没有东西就一直处于挂起状态
        std::time_t now = std::chrono::system_clock::to_time_t(timestamp);

        std::cout << now << std::endl; // 打印时间戳（单位秒）
        int sz = result.size();

        // if (sz == 0)
        //     std::cout << "ERROR: Subscribe Target Not found!" << std::endl; // 这个不会发生，因为如果为空不会publish

        for (int i = 0; i < sz; ++i)
        {
            detection::PrintInfo(result[i], classNames); // 只有一个输出，不需要锁，不会和notfound冲突
        }
    }
}