/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 21:28:54
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-08 22:48:42
 */
#include "detection/core.hpp"

using namespace std;
using namespace cv;
using namespace dnn;
/// @brief 使用ONNX模型检测
/// @tparam _Tp
/// @param task Class Yolov8Onnx
/// @param img  Mat输入图像
/// @param model_path onnx路径
/// @return
int yolov8_onnx(Yolov8Onnx &task, Mat &img, string &model_path)
{
    if (task.ReadModel(model_path, false))
        cout << "read net ok!" << endl; // TODO:实际上没有用，待解决_asset问题
    else
        return -1;

    vector<Scalar> color;
    srand(time(0));
    for (int i = 0; i < 10; i++) // TODO 不需要随机颜色，只需要一种检测框就行了
    {
        int b = 0;
        int g = 0;
        int r = 256;
        color.push_back(Scalar(b, g, r));
    }

    vector<OutputParams> result;

    if (task.OnnxDetect(img, result))
        DrawPred(img, result, task._className, color);
    else
        cout << "Detect Failed!" << endl;

    cv::waitKey(0);
    // system("pause");
    return 0;
}

/// @brief 主要运行文件，执行检测的main
void detection::core()
{

    string img_path = "detection/database/6.jpg";

    string model_path_detect = "detection/weights/best.onnx";

    Mat src = imread(img_path);
    Mat img = src.clone();

    Yolov8Onnx task_detect_ort;

    yolov8_onnx(task_detect_ort, img, model_path_detect);

#ifdef VIDEO_OPENCV
    video_demo(task_detect_ocv, model_path_detect);
    // video_demo(task_segment_ocv, model_path_seg);
#else
    // video_demo(task_detect_ort, model_path_detect);
    // video_demo(task_rtdetr_ort, model_path_rtdetr);
    // video_demo(task_segment_ort, model_path_seg);
#endif
}

// TODO 检测视频
/*
    template <typename _Tp>
    int video_demo(_Tp &task, string &model_path)
    {
        vector<Scalar> color;
        srand(time(0));
        for (int i = 0; i < 80; i++)
        {
            int b = rand() % 256;
            int g = rand() % 256;
            int r = rand() % 256;
            color.push_back(Scalar(b, g, r));
        }
        vector<OutputParams> result;
        cv::VideoCapture cap(0);
        if (!cap.isOpened())
        {
            std::cout << "open capture failured!" << std::endl;
            return -1;
        }
        Mat frame;
#ifdef VIDEO_OPENCV
        Net net;
        if (task.ReadModel(net, model_path, true))
        {
            cout << "read net ok!" << endl;
        }
        else
        {
            cout << "read net failured!" << endl;
            return -1;
        }

#else
        if (task.ReadModel(model_path, true))
        {
            cout << "read net ok!" << endl;
        }
        else
        {
            cout << "read net failured!" << endl;
            return -1;
        }

#endif

        while (true)
        {

            cap.read(frame);
            if (frame.empty())
            {
                std::cout << "read to end" << std::endl;
                break;
            }
            result.clear();
#ifdef VIDEO_OPENCV

            if (task.Detect(frame, net, result))
            {
                DrawPred(frame, result, task._className, color, true);
            }
#else
            if (task.OnnxDetect(frame, result))
            {
                DrawPred(frame, result, task._className, color, true);
            }
#endif
            int k = waitKey(10);
            if (k == 27)
            { // esc
                break;
            }
        }
        cap.release();

        system("pause");

        return 0;
    }
    */