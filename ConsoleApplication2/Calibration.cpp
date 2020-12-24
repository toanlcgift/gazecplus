#include "Calibration.h"

Calibration::Calibration()
{
}

bool Calibration::is_complete()
{
	return false;
}

double Calibration::find_best_threshold(cv::Mat frame)
{
	return 0.0;
}

void Calibration::evaluate(cv::Mat frame, int side)
{
	auto thresh_hold = find_best_threshold(frame);
	double average_iris_size = 0.48;
}

