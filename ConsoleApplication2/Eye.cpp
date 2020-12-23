#include "Eye.h"

using namespace std;

Eye::Eye(cv_image<bgr_pixel> frame, full_object_detection landmarks, int side, Calibration calibration)
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

void Eye::isolate(cv_image<bgr_pixel> frame, full_object_detection landmarks, int inputs[6])
{
	//auto height = frame
	
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

void Eye::analyze(cv_image<bgr_pixel> frame, full_object_detection landmarks, int side, Calibration calibration)
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
}


