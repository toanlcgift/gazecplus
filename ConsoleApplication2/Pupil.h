#pragma once
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
using namespace dlib;
class Pupil
{
public:
	Pupil(cv_image<bgr_pixel> eye_frame);
};