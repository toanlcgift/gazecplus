#include "Calibration.h"

Calibration::Calibration()
{
}

bool Calibration::is_complete()
{
	return thresholds_left.size() >= nb_frames && thresholds_right.size() >= nb_frames;
}

double Calibration::find_best_threshold(cv::Mat frame)
{
	return 0.0;
}

double Calibration::iris_size(cv::Mat frame)
{
	return 0.0;
}

int Calibration::threshold(int side)
{
	if (side == 0) {
		return (int)getSum(thresholds_left) / thresholds_left.size();
	}
	else if (side == 1) {
		return (int)getSum(thresholds_right) / thresholds_right.size();
	}
	return 0;
}

double Calibration::getSum(std::vector<double> input)
{
	double sum_of_elems = 0;
	for (std::vector<double>::iterator it = input.begin(); it != input.end(); ++it)
		sum_of_elems += *it;
}

void Calibration::evaluate(cv::Mat frame, int side)
{
	auto thresh_hold = find_best_threshold(frame);
	double average_iris_size = 0.48;
}

