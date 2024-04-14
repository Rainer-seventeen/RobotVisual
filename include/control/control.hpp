/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-14 20:05:55
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 21:25:32
 */
#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "control/define.hpp"
#include "detection/detection_pack.hpp"
#include "detection/core.hpp"
#include "umt/umt.hpp"
#include <string>
#include <iostream>

namespace control
{
    void core();
} // namespace control

const std::vector<std::string> classNames{
    "cup"};

#endif
