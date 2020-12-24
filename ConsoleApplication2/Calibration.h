#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Calibration
{
public:
	Calibration();
	bool is_complete();
	void evaluate(cv::Mat frame, int side);
private:
	double find_best_threshold(cv::Mat frame);
};

