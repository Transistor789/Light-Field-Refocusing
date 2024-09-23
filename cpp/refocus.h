#ifndef REFOCUS_H
#define REFOCUS_H

#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat refocus(const cv::Mat& LF, const float& alpha);

#endif // !REFOCUS_H