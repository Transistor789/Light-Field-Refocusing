#ifndef LOADLF_H
#define LOADLF_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;

std::pair<int, int> parseFileName(const std::string& filename);
cv::Mat loadLF(const std::string& path);
void display(cv::Mat LF, int u, int v);

#endif // !LOADLF_H