#include <iostream>
#include <cmath>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

void myCircle(int dx, int dy, cv::Mat& image, cv::Scalar scalar);

#define PI 3.141592

int main()
{
	Mat image(400, 400, CV_8UC3, Scalar(0, 0, 255));
	//cout << image << endl;
	namedWindow("window");
	imshow("window", image);
	waitKey(0);
	for (int i = 0; i < 36; i++)
	{
		cout << sin(PI / 180 * i *10) << endl;
	}
	myCircle(200, 100, image, Scalar(100,100,100));
	imshow("window", image);
	waitKey(0);
	for (int i = 10; i > 0; i--)
	{
		circle(image, Point(200, 200), i*10, Scalar(255, 0, i*20), i*10);
		arrowedLine(image, Point(100, 100), Point(200, 200), Scalar(0, 255, 0), 3);
	}
	imshow("window", image);
	waitKey(0);
	return 0;
}

/**
Ez egy komment
*/
void myCircle(int dx, int dy, cv::Mat& image, cv::Scalar scalar)
{
	for (double i = 0;i < 360;i++)
	{
		double radius = 100;
		int x = (int)(radius*sin(PI / 180 * i));
		int y = (int)(radius*cos(PI / 180 * i));
		if (x < 0 || y < 0) continue;
		image.at<Vec3b>(x, y)[0] = (char) scalar[0];
		image.at<Vec3b>(x, y)[1] = (char) scalar[1];
		image.at<Vec3b>(x, y)[2] = (char) scalar[2];
	}
}
