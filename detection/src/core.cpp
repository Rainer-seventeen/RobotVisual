/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 21:28:54
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-12 20:44:38
 */
#include "detection/core.hpp"

using namespace std;
using namespace cv;
using namespace dnn;

#define VIDEO
#define DEBUG

/// @brief 使用ONNX模型检测
/// @tparam _Tp
/// @param task Class Yolov8Onnx
/// @param img  Mat输入图像
/// @param model_path onnx路径
/// @return
int yolov8_onnx(Yolov8Onnx &task, Mat &img, string &model_path, vector<OutputParams> &result)
{
    if (task.ReadModel(model_path, false))
        cout << "read net ok!" << endl; // 如果路径不存在，不会报错。
    else
        return -1;

    if (!task.OnnxDetect(img, result))
        cout << "Detect Failed!" << endl;

    return 0;
}

/// @brief 主要运行文件，执行检测的main，用于被run函数调用
void detection::core()
{

    // 获取当前文件地址
    char *buffer;
    // 也可以将buffer作为输出参数
    if ((buffer = getcwd(NULL, 0)) == NULL)
    {
        perror("getcwd error");
        return;
    }

    string model_path_detect = buffer;
    model_path_detect += "/detection/weights/best.onnx";
    std::cout << model_path_detect << std::endl;

    Yolov8Onnx task_detect_ort;
    vector<OutputParams> result; // 结果存储信息

#ifndef VIDEO
    string img_path = "detection/database/3.jpg";

    Mat src = imread(img_path);
    Mat img = src.clone();

    yolov8_onnx(task_detect_ort, img, model_path_detect, result);

    // 测试结果，输出
    vector<int>::size_type sz = result.size();
    if (sz == 0)
        std::cout << "ERROR:Target Not Found!" << endl;
    else
    {
        std::cout << "<======DetectionData======>" << endl;
        for (int i = 0; i < sz; i++)
        {
            std::cout << "POINT      :" << i << endl;
            std::cout << "rec-x      :" << result[i].box.x << endl;
            std::cout << "rec-y      :" << result[i].box.y << endl;
            std::cout << "rec-w      :" << result[i].box.width << endl;
            std::cout << "rec-h      :" << result[i].box.height << endl;
            std::cout << "confidence :" << result[i].confidence << endl;
            std::cout << "id         :" << task_detect_ort._className[result[i].id] << endl;
        }
    }
    // TODO 目前输出坐标和框的逻辑，不适用于摄像头

    DrawPred(img, result, task_detect_ort._className);
    cv::waitKey(0);

#else

    cv::VideoCapture cap(0);
    // 读取，打开摄像头
    if (!cap.isOpened())
    {
        std::cout << "ERROR: Open Capture Failed!" << std::endl;
        return;
    }

#ifdef DEBUG
    std::cout << "TASK: Captrue Opened" << std::endl;
#endif

    Mat frame;

    if (task_detect_ort.ReadModel(model_path_detect, true))
        cout << "TASK: Read Net OK!" << endl;
    else
        cout << "ERROR: Read Net Failed!" << endl;

    while (true)
    {
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "ERROR:Failed To Read Frame From Camera!" << std::endl;
            break;
        }
        result.clear();

        // auto begin = std::chrono::high_resolution_clock::now(); // 测试时间用，起始时间
        task_detect_ort.OnnxDetect(frame, result);
        // auto end = std::chrono::high_resolution_clock::now();
        // auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        // printf(" %.3f ms.\n", elapsed.count() * 1e-6);

        DrawPred(frame, result, task_detect_ort._className, true);
        PrintInf(result, task_detect_ort._className);
        waitKey(1);
    }

    cap.release();
    destroyAllWindows();

#endif
}

#if 0
template <typename _Tp>
int video_demo(_Tp &task, std::string &model_path)
{
    vector<OutputParams> result;
    cv::VideoCapture cap(0);
    // 读取，打开摄像头 if (!cap.isOpened())
    {
        std::cout << "open capture failured!" << std::endl;
        return -1;
    }
    Mat frame;

    if (task.ReadModel(model_path, true))
        cout << "read net ok!" << endl;
    else
    {
        cout << "read net failured!" << endl;
        return -1;
    }

    while (true)
    {
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "read to end" << std::endl;
            break;
        }
        result.clear();

        if (task.OnnxDetect(frame, result))
        {
            DrawPred(frame, result, task._className, true);
        }

        int k = waitKey(10);
        if (k == 27)
        { // esc
            break;
        }
    }
    cap.release();

    waitKey(0);
    return 0;
}

#endif