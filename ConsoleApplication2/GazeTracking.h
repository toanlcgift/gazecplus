#pragma once
#include "Eye.h"
class GazeTracking
{
public: GazeTracking();
	  void setEyeLeft(Eye eye);
	  void setEyeRight(Eye eye);
	  Calibration getCalibration();
private:
	Eye eye_left = Eye();
	Eye eye_right = Eye();
	Calibration calibration;
	cv_image<unsigned char> frame;
};

