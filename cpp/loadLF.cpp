#include "loadLF.h"

std::pair<int, int> parseFileName(const std::string& filename) {
	size_t underscorePos = filename.find('_');
	size_t dotPos = filename.find('.');

	int num1 = std::stoi(filename.substr(0, underscorePos));
	int num2 = std::stoi(filename.substr(underscorePos + 1, dotPos - underscorePos - 1));

	return { num1, num2 };
}
cv::Mat loadLF(const std::string& path) {
	std::vector<fs::path> files;

	for (const auto& entry : fs::directory_iterator(path)) {
		files.push_back(entry.path());
	}
	std::sort(files.begin(), files.end(), [](const fs::path& a, const fs::path& b) {
		return parseFileName(a.filename().string()) < parseFileName(b.filename().string());
		});

	int count = 0;
	int countMax = files.size();
	int uvMax = static_cast<int>(sqrt(countMax));
	cv::Mat image = cv::imread(path + files[0].filename().string(), CV_8U);
	int size = image.total();
	int dims[4] = { uvMax, uvMax, image.rows, image.cols };
	cv::Mat LF(4, dims, CV_8U);
	memcpy(LF.ptr<uchar>(), image.ptr<uchar>(), size * sizeof(uchar));

	while (count < countMax) {
		cv::Mat image = cv::imread(path + files[count].filename().string(), CV_8U);
		memcpy(LF.ptr<uchar>() + count * size, image.ptr<uchar>(), size * sizeof(uchar));
		count++;
	}

	return LF;
}
void display(cv::Mat LF, int u, int v) {
	if (0 <= u && u <= LF.size[0] && 0 <= v && v <= LF.size[1]) {
		cv::Mat image(LF.size[2], LF.size[3], LF.type(), LF.ptr<uchar>(u - 1, v - 1));

		cv::imshow("image", image);
		cv::waitKey();
	}
	else {
		printf("error\n");
	}
}