#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "loadLF.h"
#include "refocus.h"


int main() {
	float alpha = 1.25;
	std::string path = "../input/";

	cv::Mat LF = loadLF(path);
	auto start = std::chrono::high_resolution_clock::now();
	cv::Mat refocusedImage = refocus(LF, alpha);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	printf("Time elapsed: %.3f ms\n", duration.count() * 1000);

	cv::imshow("refocusedImage", refocusedImage);
	cv::waitKey();

	return 0;
}