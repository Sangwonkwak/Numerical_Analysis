//file I/O and resize with interpolation
#include <opencv2/opencv.hpp>
#include <iostream>

void BilinearInterpolation(cv::Mat &src, cv::Mat &dst,double scale_rate);
cv::Mat bi_dst;

int main()
{
	cv::Mat src;
	src = cv::imread("lena.jpg", 1);  //절대 경로 혹은 상대 경로(0은 gray scale)
	if (src.empty())
	{
		std::cout << "Cannot find an image" << std::endl;
		return -1;
	}
	cv::imshow("SourceImage", src);
	cv::waitKey(0);

	//이미지를 scale_rate배 했을때의 Bilinear interpolation
	double scale_rate = 1.5;
	int height = src.rows * scale_rate;
	int width = src.cols * scale_rate;
	bi_dst = cv::Mat(height, width, src.type(), cv::Scalar(0,0,0)); //결과물을 담을 Mat

	//bilinearInterpolation
	BilinearInterpolation(src, bi_dst,scale_rate);
	cv::imshow("BIImage", bi_dst);
	cv::waitKey(0);

	return 0;
}

void BilinearInterpolation(cv::Mat &src, cv::Mat &dst,double scale_rate){
	double s = scale_rate; //scale_rate short notation
	int x[2], y[2]; //주위의 4점의 좌표
	double a, b; // 거리
	for (int j = 0; j < dst.cols; j++){
		for (int i = 0; i < dst.rows; i++) {
			x[0] = (int)(i / s);
			y[0] = (int)(j / s);
			a = i / s - (double)x[0];
			b = j / s - (double)y[0];

			if (x[0] < src.rows-1) x[1] = x[0] + 1;
			else x[1] = x[0];
			if (y[0] < src.cols-1) y[1] = y[0] + 1;
			else y[1] = y[0];

			//RGB 각 data에 대해 bilinear interpolation
			for (int k = 0; k < 3; k++) {
				dst.at<cv::Vec3b>(j, i)[k] = (1.0 - a) * (1.0 - b) * src.at<cv::Vec3b>(y[0], x[0])[k]
					+ a * (1.0 - b) * src.at<cv::Vec3b>(y[0], x[1])[k]
					+ (1.0 - a) * b * src.at<cv::Vec3b>(y[1], x[0])[k]
					+ a * b * src.at<cv::Vec3b>(y[1], x[1])[k];
			}
		}
	}
}