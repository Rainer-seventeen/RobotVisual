/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 21:28:54
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 21:12:39
 */
#include "detection/core.hpp"

using namespace std;
using namespace cv;
using namespace dnn;

#define VIDEO

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

/**
 * @description: 获取onnx文件
 * @return {*}
 */
std::string detection::get_model_path()
{
    char *buffer;
    if ((buffer = getcwd(NULL, 0)) == NULL)
    {
        std::cout << "ERROR: Cannot Get Current Directory!" << std::endl; // DEBUG
        return "ERROR";
    }

    string model_path_detect = buffer;
    model_path_detect += "/detection/weights/best.onnx";
    return model_path_detect;
}

/// @brief 主要运行文件，执行检测的main，用于被run函数调用
void detection::core()
{
    /*获取模型路径*/
    string model_path_detect = get_model_path();
    std::cout << "Model Path : ";
    std::cout << model_path_detect << std::endl; // DEBUG

    /*创建类的实例*/
    Yolov8Onnx task_detect_ort;
    vector<OutputParams> result;                                      // 结果存储信息
    umt::Publisher<Detection_pack> detections_pub("detections_pack"); // 检测结果整合包发布器
    // umt::Subscriber<SensorsData> sensor_sub("sensors_data");  // TODO 订阅传感器信息
    Mat frame;

    /*读取摄像头*/
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "ERROR: Open Capture Failed!" << std::endl; // DEBUG
        return;
    }
    std::cout << "TASK: Captrue Opened" << std::endl; // DEBUG

    /*加载神经网络*/
    if (task_detect_ort.ReadModel(model_path_detect, true))
        cout << "TASK: Read Net OK!" << endl;
    else
        cout << "ERROR: Read Net Failed!" << endl;

    int cnt_useless = -1;
    /*检测循环流程*/
    while (true)
    {
        Timestamp now = std::chrono::system_clock::now(); // 拿到当前时间戳
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

        /*输出检测结果*/
        DrawPred(frame, result, task_detect_ort._className, true); // 绘制结果，内部包含了输出到控制台
        if (waitKey(1) == 27)                                      // ESC
            break;

        /*发布检测结果*/
        if (!result.empty())
        {
            detections_pub.push(Detection_pack{result, now}); // 打包数据,包括检测结果和时间戳
        }
        else
        {
            if (++cnt_useless == 50)
            { // 避免输出太多
                fmt::print(fmt::fg(fmt::color::blue), "No Target detected!");
                std::cout << std::endl;
                cnt_useless = -1;
            }
            // webview_detections.push(img);
            continue;
        }
    }

    cap.release();
    destroyAllWindows();
}

void detection::PrintInfo(const OutputParams oneresult, std::vector<std::string> classNames)
{

    std::cout << "<======DetectionData======>" << std::endl;

    std::cout << "rec-x      :" << oneresult.box.x << std::endl;
    std::cout << "rec-y      :" << oneresult.box.y << std::endl;
    std::cout << "rec-w      :" << oneresult.box.width << std::endl;
    std::cout << "rec-h      :" << oneresult.box.height << std::endl;
    std::cout << "confidence :" << oneresult.confidence << std::endl;
    std::cout << "id         :" << classNames[oneresult.id] << std::endl;
}