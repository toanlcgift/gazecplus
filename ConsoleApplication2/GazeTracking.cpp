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

Eye GazeTracking::getEyeLeft()
{
	return eye_left;
}

Eye GazeTracking::getEyeRight()
{
	return eye_right;
}

Calibration GazeTracking::getCalibration()
{
	return calibration;
}

bool GazeTracking::pupils_located()
{
	return false;
}
