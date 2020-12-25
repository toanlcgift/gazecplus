#include "Calibration.h"
#include "Pupil.h"

Calibration::Calibration()
{
}

bool Calibration::is_complete()
{
	return thresholds_left.size() >= nb_frames && thresholds_right.size() >= nb_frames;
}

double Calibration::find_best_threshold(cv::Mat frame)
{
	double average_iris_size = 0.48;
	std::map<int, double> trials;

	for (int i = 5; i < 100; i += 5) {
		auto iris_frame = Pupil::image_processing(frame, i);
		trials.insert(std::pair<int, double>(i, Pupil::iris_size(iris_frame)));
	}

	return 0.0;
}

double Calibration::iris_size(cv::Mat frame)
{

	cv::Mat new_frame(frame, cv::Rect(cv::Point(5, 5), cv::Point(-5, -5)));
	//cv::imwrite("new_frame.png",new_frame);
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
	return sum_of_elems;
}

void Calibration::evaluate(cv::Mat frame, int side)
{
	auto thresh_hold = find_best_threshold(frame);

	if (side == 0) {
		thresholds_left.push_back(thresh_hold);
	}
	else if (side == 1) {
		thresholds_right.push_back(thresh_hold);
	}
}

