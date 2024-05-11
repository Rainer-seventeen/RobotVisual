/*
 * @Author       : Rainer-seventeen 1652018592@qq.com
 * @Date         : 2024-04-08 16:32:14
 * @LastEditors  : Rainer-seventeen
 * @LastEditTime : 2024-04-14 21:17:09
 */
#pragma once
#include <iostream>
#include <numeric>
#include <opencv2/opencv.hpp>
#include <sys/io.h>
#include "detection/detection_pack.hpp"
#define ORT_OLD_VISON 13

const cv::Scalar COLOR(0, 0, 256);

struct MaskParams
{
	// int segChannels = 32;
	// int segWidth = 160;
	// int segHeight = 160;
	int netWidth = 640;
	int netHeight = 640;
	float maskThreshold = 0.5;
	cv::Size srcImgShape;
	cv::Vec4d params;
};
// bool CheckModelPath(std::string modelPath);
bool CheckParams(int netHeight, int netWidth, const int *netStride, int strideSize);
void DrawPred(cv::Mat &img,
			  std::vector<OutputParams> result,
			  std::vector<std::string> classNames,
			  bool isVideo = false);
void DrawRotatedBox(cv::Mat &srcImg, cv::RotatedRect box, int thinkness);
void LetterBox(const cv::Mat &image, cv::Mat &outImage,
			   cv::Vec4d &params, //[ratio_x,ratio_y,dw,dh]
			   const cv::Size &newShape = cv::Size(640, 640),
			   bool autoShape = false,
			   bool scaleFill = false,
			   bool scaleUp = true,
			   int stride = 32,
			   const cv::Scalar &color = cv::Scalar(114, 114, 114));
void GetMask(const cv::Mat &maskProposals, const cv::Mat &maskProtos, std::vector<OutputParams> &output, const MaskParams &maskParams);
void GetMask2(const cv::Mat &maskProposals, const cv::Mat &maskProtos, OutputParams &output, const MaskParams &maskParams);
int BBox2Obb(float centerX, float centerY, float boxW, float boxH, float angle, cv::RotatedRect &rotatedRect);
void PrintInfo(OutputParams oneresult,
			   std::vector<std::string> classNames);