#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include "Calibration.h"

using namespace dlib;

class Eye
{
public:
	Eye(cv_image<bgr_pixel> frame, full_object_detection landmarks, int side, Calibration calibration); //size = 0 || 1
	Eye();

private:
	int leftpoints[6] = { 36, 37, 38, 39, 40, 41 };
	int rightpoints[6] = { 42, 43, 44, 45, 46, 47 };
	int points[6];
	double blinking;
	double middle_point(long a, long b);
	void analyze(cv_image<bgr_pixel> frame, full_object_detection landmarks, int side, Calibration calibration);
	double blinking_ratio(full_object_detection landmarks, int inputs[6]);
	
};