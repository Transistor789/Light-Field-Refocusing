#include "refocus.h"

cv::Mat refocus(const cv::Mat& LF, const float& alpha) {
	int umax = LF.size[0];
	int vmax = LF.size[1];
	int xmax = LF.size[2];
	int ymax = LF.size[3];
	int uC = static_cast<int>(umax / 2);
	int vC = static_cast<int>(vmax / 2);
	float factor = 1 - 1 / alpha;

	cv::Mat refocusedImage(xmax, ymax, CV_32F, cv::Scalar(0));
	cv::Mat image(xmax, ymax, CV_8U, cv::Scalar(0));
	cv::Mat xgrid(xmax, 1, CV_32F);
	cv::Mat ygrid(1, ymax, CV_32F);
	for (int x = 0; x < xmax; x++) {
		xgrid.at<float>(x, 0) = static_cast<float>(x);
	}
	for (int y = 0; y < ymax; y++) {
		ygrid.at<float>(0, y) = static_cast<float>(y);
	}
	xgrid = cv::repeat(xgrid, 1, ymax);
	ygrid = cv::repeat(ygrid, xmax, 1);

	cv::Mat temp;
	for (int u = 0; u < umax; u++) {
		for (int v = 0; v < vmax; v++) {
			memcpy(image.ptr<uchar>(), LF.ptr<uchar>(u, v), xmax * ymax * sizeof(uchar));
			cv::remap(image, temp, ygrid + factor * (v - vC), xgrid + factor * (u - uC), cv::INTER_LINEAR, cv::BORDER_REFLECT);
			refocusedImage += temp;
		}
	}
	refocusedImage /= (umax * vmax);
	refocusedImage.convertTo(refocusedImage, CV_8U);

	return refocusedImage;
}