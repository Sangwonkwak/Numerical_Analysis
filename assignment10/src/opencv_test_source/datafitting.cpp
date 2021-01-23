#include <iostream>
#include <opencv2/core.hpp>
#include <fstream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"


using namespace cv;
using namespace std;

Mat AddGaussianNoise(Mat &src);
Mat MaskedNoise(Mat &src);
void MatchedKeyPoint(Mat &src1, Mat &src2);

//global variable
int distThresh = 30;
vector<Point2f> Left;
vector<Point2f> Right;

int main()
{
	float** H, * k, * a, r, d;
	int* indx = (int*)malloc(sizeof(int) * 9);
	k = (float*)malloc(sizeof(float) * 9);
	a = (float*)malloc(sizeof(float) * 9);
	H = (float**)malloc(sizeof(float*) * 9);
	for (int i = 0; i < 9; i++) H[i] = (float*)malloc(sizeof(float) * 9);

	int N;//correspondence 개수
	ofstream out("test_bad.txt");
	Mat LeftImg = imread("badLeft.jpg");
	Mat RightImg = imread("badRight.jpg");
	//image가 너무 클 경우 사이즈 조정
	resize(LeftImg, LeftImg, Size(), 0.5, 0.5, INTER_LINEAR);
	resize(RightImg, RightImg, Size(), 0.5, 0.5, INTER_LINEAR);

	//0. normal case
	
	//1.Add Gaussian noise
	//RightImg = AddGaussianNoise(RightImg);

	//2. Add Gaussian noise + addtional noise;
	//RightImg = MaskedNoise(RightImg);
	
	//Extract features and matching correspondence
	MatchedKeyPoint(LeftImg, RightImg);
	N = Left.size();
	//cout << Left.size() << endl;
	//cout << Right.size() << endl;

	//correspondence points printed out to file
	out << N << endl;
	for (int i = 0; i < N; i++)
		out << Left[i].x << " " << Left[i].y << " " << Right[i].x << " " << Right[i].y << endl;
	out.close();
	return 0;
}

Mat AddGaussianNoise(Mat &src)
{
	Mat noise_src(src.size(), src.type());
	double average = 0.0;
	double std = 30.0;
	randn(noise_src, Scalar::all(average), Scalar::all(std));

	Mat tmp_img;
	src.convertTo(tmp_img, src.type());
	addWeighted(tmp_img, 1.0, noise_src, 1.0, 0.0, tmp_img);

	imshow("tmp", tmp_img);
	waitKey(0);

	return tmp_img;
}

Mat MaskedNoise(Mat &src)
{
	Mat noised_mask = imread("C:/Users/Nam/source/repos/NA_interpolation_datafitting/NA_interpolation_datafitting/masking1.jpg");
	resize(noised_mask, noised_mask, Size(src.cols, src.rows));
	
	Mat mask1 = Mat::zeros(src.rows, src.cols, CV_32F);
	Mat mask2 = Mat::zeros(src.rows, src.cols, CV_32F);
	rectangle(mask1, Rect(0, 0, src.cols, src.rows), Scalar(0.8f), FILLED);
	rectangle(mask2, Rect(0, 0, src.cols, src.rows), Scalar(0.2f), FILLED);
	Mat result = Mat(src.rows, src.cols, CV_8UC3);
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			result.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(y, x) * mask1.at<float>(y, x) 
				+ noised_mask.at<cv::Vec3b>(y, x) * mask2.at<float>(y, x);
		}
	}
	
	Mat noise_src(result.size(), result.type());
	double average = 0.0;
	double std = 50.0;
	randn(noise_src, Scalar::all(average), Scalar::all(std));

	Mat tmp_img;
	result.convertTo(tmp_img, result.type());
	addWeighted(tmp_img, 1.0, noise_src, 1.0, 0.0, tmp_img);

	return tmp_img;
}


void MatchedKeyPoint(Mat &src1, Mat &src2)
{
	Ptr<Feature2D> featureExtractor;
	featureExtractor = ORB::create();
	vector<KeyPoint> LeftKeypoints, RightKeypoints;
	Mat LeftDescriptors, RightDescriptors;
	Mat matchingImage;
	featureExtractor->detectAndCompute(src1, Mat(), LeftKeypoints, LeftDescriptors);
	featureExtractor->detectAndCompute(src2, Mat(), RightKeypoints, RightDescriptors);
	//imshow("left", LeftDescriptors);
	//cout << LeftKeypoints.size() << endl;
	//cout << RightKeypoints.size() << endl;
	Ptr<DescriptorMatcher> matcher;
	vector<vector<DMatch>> knnMatches;
	vector<DMatch> matches;

	matcher = DescriptorMatcher::create("BruteForce-Hamming");
	matcher->match(LeftDescriptors, RightDescriptors, matches);
	vector<DMatch>::iterator it = matches.begin();
	for (; it != matches.end(); )
	{
		if (it->distance > distThresh)
		{	
			it = matches.erase(it);
		}
		else
		{
			it++;
		}
	}
	cout << matches.size() << endl;
	drawMatches(src1, LeftKeypoints, src2, RightKeypoints, matches, matchingImage);

	imshow("matches", matchingImage);
	waitKey(0);

	for (int i = 0; i < matches.size(); i++)
	{
		//Left이 src1의 point들, Right이 src2의 point들
		Left.push_back(LeftKeypoints[matches[i].queryIdx].pt);
		Right.push_back(RightKeypoints[matches[i].trainIdx].pt);
	}

}