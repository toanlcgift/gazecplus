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
	double getX();
	double getY();
private:
	double x;
	double y;
	cv::Mat iris_frame;
	int thresh_hold;
	//bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2);
	void detect_iris(cv::Mat eye_frame);
};