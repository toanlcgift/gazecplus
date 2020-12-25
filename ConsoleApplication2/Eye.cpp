#include "Eye.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

Eye::Eye(cv_image<unsigned char> frame, full_object_detection landmarks, int side, Calibration calibration)
{
	this->frame = frame;
	this->landmarks = landmarks;
	this->calibration = calibration;
	analyze(frame, landmarks, side, calibration);
}

Eye::Eye()
{
}


double Eye::middle_point(long a, long b)
{
	return (double)((a + b) / 2);
}

void Eye::isolate(cv_image<unsigned char> frame, full_object_detection landmarks, int inputs[6])
{
	auto height = frame.nr();
	auto width = frame.nc();
	cv::Mat black_image = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
	cv::Mat mask(height, width, CV_8UC1, cv::Scalar(255, 255, 255));

	std::vector<std::vector<cv::Point>> imagePoints;
	std::vector<cv::Point> points;
	std::vector<long> xArrays;
	std::vector<long> yArrays;

	for (int i = 0; i < 6; i++) {
		points.push_back(cv::Point(landmarks.part(inputs[i]).x(), landmarks.part(inputs[i]).y()));
		xArrays.push_back(landmarks.part(inputs[i]).x());
		yArrays.push_back(landmarks.part(inputs[i]).y());
	}
	imagePoints.push_back(points);
	cv::fillPoly(mask, imagePoints, cv::Scalar(0, 0, 0));
	cv::Mat frameCV;
	frameCV = dlib::toMat(frame);
	cv::Mat eye;
	frameCV.copyTo(eye);
	cv::bitwise_not(black_image, eye, mask);

	long margin = 5;

	long min_x = *min_element(xArrays.begin(), xArrays.end()) - margin;
	long max_x = *max_element(xArrays.begin(), xArrays.end()) + margin;
	long min_y = *min_element(yArrays.begin(), yArrays.end()) - margin;
	long max_y = *max_element(yArrays.begin(), yArrays.end()) + margin;

	this->eye_frame= cv::Mat(eye, cv::Rect(cv::Point(min_x, min_y), cv::Point(max_x, max_y)));

	originX = min_x;
	originY = min_y;

	auto croppedHeight = this->eye_frame.rows;
	auto croppedWidth = this->eye_frame.cols;

	centerX = (double)(croppedWidth / 2);
	centerY = (double)(croppedHeight / 2);

	//cv::imwrite("cropped.png", cropped);
}

long Eye::getOriginX()
{
	return originX;
}

long Eye::getOriginY()
{
	return originY;
}

double Eye::getCenterX()
{
	return centerX;
}

double Eye::getCenterY()
{
	return centerY;
}


double Eye::blinking_ratio(full_object_detection landmarks, int inputs[6])
{
	auto leftX = landmarks.part(inputs[0]).x();
	auto leftY = landmarks.part(inputs[0]).y();

	auto rightX = landmarks.part(inputs[3]).x();
	auto rightY = landmarks.part(inputs[3]).y();

	auto topX = middle_point(landmarks.part(inputs[1]).x(), landmarks.part(inputs[2]).x());
	auto topY = middle_point(landmarks.part(inputs[1]).y(), landmarks.part(inputs[2]).y());

	auto bottomX = middle_point(landmarks.part(inputs[5]).x(), landmarks.part(inputs[4]).x());
	auto bottomY = middle_point(landmarks.part(inputs[5]).y(), landmarks.part(inputs[4]).y());

	auto eye_width = cv::sqrt((leftX - rightX) * (leftX - rightX) + (leftY - rightY) * (leftY - rightY));
	auto eye_height = cv::sqrt((topX - bottomX) * (topX - bottomX) + (topY - bottomY) * (topY - bottomY));
	if (eye_height == 0)
		return 0.0;
	else
		return eye_width / eye_height;
}

void Eye::analyze(cv_image<unsigned char> frame, full_object_detection landmarks, int side, Calibration calibration)
{
	for (int i = 0; i < 6; i++) {
		if (side == 0) {
			points[i] = leftpoints[i];
		}
		else if (side == 1) {
			points[i] = rightpoints[i];
		}
		else
			return;
	}
	blinking = blinking_ratio(landmarks, points);
	isolate(frame, landmarks, points);
	if (!calibration.is_complete()) {
		calibration.evaluate(eye_frame, side);
	}
	auto threshold = calibration.threshold(side);
	pupil = Pupil(eye_frame, threshold);
}

Pupil Eye::getPupil()
{
	return pupil;
}


