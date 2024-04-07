/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-07 17:13:56
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-07 20:45:55
 */
#include <iostream>
#include <cstring>

#include "detection/detection.hpp"

void detection::test()
{
    std::cout << "Hello World!" << std::endl;
}

void detection::classification()
{
    // 装载模型，设置参数
    // clock_t st = clock();
    std::string model = "detecion/weights/best.onnx";

    cv::dnn::ClassificationModel dnn_model(model);
    dnn_model.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    dnn_model.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

    float scale = 1.0 / 255;
    int inpWidth = 1920, inpHeight = 1280;
    cv::Scalar mean(0, 0, 0);
    dnn_model.setInputParams(scale, cv::Size(inpWidth, inpHeight), mean, true, false);

    // clock_t end = clock();
    // std::cout << end - st << std::endl;

    // 图像文件夹遍历检测
    std::string folder = "detecion/database";
    std::vector<std::string> imagePathList;
    cv::glob(folder, imagePathList);

    std::cout << "test In C++!" << std::endl;
    for (int i = 0; i < imagePathList.size(); i++)
    {
        cv::Mat img = cv::imread(imagePathList[i]);
        // cv::resize(img, img, cv::Size(224, 224), 0, 0, cv::INTER_LANCZOS4);
        cv::Mat img_t = cv::Mat::zeros(img.size(), CV_32FC1);

        for (int ii = 0; ii < img.cols; ii++)
        {
            for (int jj = 0; jj < img.rows; jj++)
            {
                img_t.at<float>(ii, jj) = img.at<uchar>(ii, jj);
            }
        }

        int classIds;
        float confs;
        double time1 = static_cast<double>(cv::getTickCount());
        dnn_model.classify(img, classIds, confs); // 前向推理，classIds是类别索引,classIds=0是划痕，classIds=1是颗粒
        double time2 = (static_cast<double>(cv::getTickCount()) - time1) / cv::getTickFrequency();
        std::cout << classIds << std::endl;
        std::cout << "time: " << time2 << std::endl;
    }
}