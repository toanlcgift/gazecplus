#pragma once
class Calibration
{
public:
	Calibration();
	bool is_complete();
	void evaluate(Mat frame, int side);
};

