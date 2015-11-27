#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat original_image, canny_image, color_canny_image;
	original_image = imread("C:\\Users\\Titusz Ozsváth\\Pictures\\Football\\MC_Barca.png");
	namedWindow("MainWindow");

	Mat dst, cdst;
	Canny(original_image, dst, 150, 160, 3);
	cvtColor(dst, cdst, CV_GRAY2BGR);

	vector<Vec2f> lines;
	//360
	//200
	HoughLines(dst, lines, 1, CV_PI / 180, 360, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		//if((pt1.y>200 && pt2.y>100) || 
			//if((rho>0 && rho<360) )
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 2, CV_AA);
		//if (pt1.y>100 && pt2.y>200)
			//line(cdst, pt1, pt2, Scalar(0, 0, 255), 2, CV_AA);
	}

	imshow("MainWindow", cdst);
	waitKey(0);
}
