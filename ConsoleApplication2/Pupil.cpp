#include "Pupil.h"

Pupil::Pupil(cv_image<unsigned char> eye_frame, int thresh_hold)
{
}

Pupil::Pupil()
{
}

cv::Mat Pupil::image_processing(cv::Mat eye_frame, int thresh_hold)
{
    return cv::Mat();
}

double Pupil::iris_size(cv::Mat frame)
{
    return 0.0;
}

double Pupil::getX()
{
    return x;
}

double Pupil::getY()
{
    return y;
}
