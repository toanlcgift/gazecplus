#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Calibration
{
public:
	Calibration();
	bool is_complete();
	void evaluate(cv::Mat frame, int side);
	int threshold(int side);
private:
	double find_best_threshold(cv::Mat frame);
	double iris_size(cv::Mat frame);
	int nb_frames = 20;
	std::vector<double> thresholds_left;
	std::vector<double> thresholds_right;
	double getSum(std::vector<double> input);
};

