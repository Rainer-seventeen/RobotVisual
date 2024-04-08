/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-07 17:13:56
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-08 22:15:02
 */
#include <iostream>
#include <cstring>

#include "detection/detection.hpp"
#include "detection/core.hpp"

const char *class_names[] = {"Abyss Shriek", "Little Knight", "Shade Soil", "Soul Tyrant"}; // 类目名称

void detection::run()
{
    // TODO:需要在这里完成subscribe模式
    core();
}