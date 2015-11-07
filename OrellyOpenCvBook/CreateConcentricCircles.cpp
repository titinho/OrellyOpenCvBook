#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat image(3, 3, CV_8UC3, Scalar(0, 0, 255));
	//cout << image << endl;
	namedWindow("window");
	imshow("window", image);
	waitKey(0);
	while(true)
	{
		cvtColor(image, image, CV_BGR2HSV);
		cout << image << endl;
		//imshow("window", image);
		if(waitKey(100)=='q') break;
	}
	return 0;
}
