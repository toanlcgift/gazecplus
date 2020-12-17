#include "GazeTracking.h"

GazeTracking::GazeTracking()
{
	calibration = Calibration();
}

void GazeTracking::setEyeLeft(Eye eye)
{
	eye_left = eye;
}

void GazeTracking::setEyeRight(Eye eye)
{
	eye_right = eye;
}

Calibration GazeTracking::getCalibration()
{
	return calibration;
}
