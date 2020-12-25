#include "Pupil.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

Pupil::Pupil(cv_image<unsigned char> eye_frame, int thresh_hold)
{
	this->thresh_hold = thresh_hold;
	detect_iris(dlib::toMat(eye_frame));
}

Pupil::Pupil()
{
}

cv::Mat Pupil::image_processing(cv::Mat eye_frame, int thresh_hold)
{
	cv::Mat kernel(3, 3, CV_8UC1, cv::Scalar(1));
	cv::Mat new_frame;
	cv::bilateralFilter(eye_frame, new_frame, 10, 15, 15);
	cv::Mat erode;
	cv::erode(new_frame, erode, kernel, cv::Point(-1, -1), 3);
	cv::Mat threshhold;
	cv::threshold(erode, threshhold, thresh_hold, 255, cv::THRESH_BINARY);
	return threshhold;
}

double Pupil::getX()
{
	return x;
}

double Pupil::getY()
{
	return y;
}

bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2)
{
	double i = fabs(contourArea(cv::Mat(contour1)));
	double j = fabs(contourArea(cv::Mat(contour2)));
	return (i <= j);
}

void Pupil::detect_iris(cv::Mat eye_frame)
{
	iris_frame = image_processing(eye_frame, this->thresh_hold);
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(eye_frame, contours, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	auto size = contours.size();

	std::sort(contours.begin(), contours.end(), compareContourAreas);

	if (size == 0)
		return;
	std::vector<cv::Point> bestContour = contours[contours.size() - 1];
	
	auto moments = cv::moments(bestContour);
	if (moments.m00 == 0)
		return;
	x = moments.m10 / moments.m00;
	y = moments.m01 / moments.m00;

}
