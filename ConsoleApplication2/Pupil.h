#pragma once
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
using namespace dlib;
class Pupil
{
public:
	Pupil(cv_image<unsigned char> eye_frame, int thresh_hold);
	Pupil();
	static cv::Mat image_processing(cv::Mat eye_frame, int thresh_hold);
	static double iris_size(cv::Mat frame);
	double getX();
	double getY();
private:
	double x;
	double y;
};