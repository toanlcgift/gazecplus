#pragma once
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
using namespace dlib;
class Pupil
{
public:
	Pupil(cv_image<unsigned char> eye_frame);
};