/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 20:06:04
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 21:29:51
 */

#include "control/control.hpp"

void control::core()
{
    std::cout << "Task: Control Model Opened!" << std::endl;
    // 考虑将数据的输出放到这里来
    // 先sub一下两个数据
    while (true)
    {
        std::cout << "AAA" << std::endl;

        umt::Subscriber<Detection_pack> detections_sub("detections_pack"); // 订阅传感器信息
        const auto &[result, timestamp] = detections_sub.pop();
        int sz = result.size();

        if (sz == 0)
        {
            std::cout << "ERROR: Subscribe Target Not found!" << std::endl;
        }

        for (int i = 0; i < sz; ++i)
        {
            detection::PrintInfo(result[i], classNames); // 只有一个输出，不需要锁，不会和notfound冲突
        }
    }
}