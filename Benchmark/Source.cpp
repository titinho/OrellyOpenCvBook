#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <chrono>
#include <iostream>

using namespace cv;
using namespace std;

//Config
const int show_filtered_image = false;

const int slider_max = 255;
int slider_hsv_min;
int slider_hsv_max;

void on_hsv_min(int pos, void*)
{
	slider_hsv_min = pos;
}

void on_hsv_max(int pos, void*)
{
	slider_hsv_max = pos;
}

void draw_blue_square(Mat& image,double width, double height)
{
	for (int row = 0;row < height;row++)
	{
		for (int column = 0;column < width;column++)
		{
			image.at<Vec3b>(row, column)[0] = 255;
			image.at<Vec3b>(row, column)[1] = 0;
			image.at<Vec3b>(row, column)[2] = 0;
		}
	}
}

int main()
{
	namedWindow("main_window");
	namedWindow("hsv_window");
	if(show_filtered_image==true) namedWindow("filtered_window");
	createTrackbar("hsv_min", "hsv_window", &slider_hsv_min, slider_max, on_hsv_min);
	createTrackbar("hsv_max", "hsv_window", &slider_hsv_max, slider_max, on_hsv_max);
	VideoCapture capture;
	capture.open("C:\\Python\\Zlatan_goal.mp4");
	double fps    = capture.get(CAP_PROP_FPS);
	double width  = capture.get(CAP_PROP_FRAME_WIDTH);
	double height = capture.get(CAP_PROP_FRAME_HEIGHT);
	double sum = 0;
	int counter = 0;
	Mat frame;
	while (counter<300)
	{
		double start_time = (double) getTickCount();

		capture.read(frame);
		//resize(frame, frame, Size(width/2, height/2));
		imshow("main_window", frame);
		Mat hsv_frame;
		//draw_blue_square(frame, width/2, height/2);
		cvtColor(frame, hsv_frame, CV_BGR2HSV);
		Mat binary_frame;
		vector<Mat> hsv_channels(3);
		split(hsv_frame, hsv_channels);
		binary_frame = hsv_channels[0];
		threshold(binary_frame, binary_frame, slider_hsv_min, slider_hsv_max, CV_THRESH_BINARY);
		imshow("hsv_window", binary_frame);

		if (show_filtered_image == true)
		{
			vector<Mat> rgb_channels(3);
			split(frame, rgb_channels);
			rgb_channels[0] &= binary_frame;
			rgb_channels[1] &= binary_frame;
			rgb_channels[2] &= binary_frame;
			merge(rgb_channels, frame);
			imshow("filtered_image", frame);
		}

		double end_time = (double)getTickCount();
		double elapsed_time = (end_time - start_time) / getTickFrequency();
		int wait_millisec = (int)round(1000 * (1 / fps) - elapsed_time * 1000);
		if (wait_millisec < 0) wait_millisec = int(1000*(1 / fps));
		//if (waitKey(wait_millisec) == 'q') break;
		if(waitKey(200)=='q') break;
		counter++;
		sum += elapsed_time;
	}
	cout << "Atlagos frame-hossz: " << sum / counter << endl;
	destroyAllWindows();
	return 0;
}