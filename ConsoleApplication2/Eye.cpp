#include "Eye.h"

using namespace std;

Eye::Eye(cv_image<bgr_pixel> frame, full_object_detection landmarks, int side, Calibration calibration)
{
}

Eye::Eye()
{
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
}

double Eye::blinking_ratio(full_object_detection landmarks, int inputs[6])
{
	return 0.0;
}
