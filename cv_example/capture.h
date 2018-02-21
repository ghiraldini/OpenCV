#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

#include "cannyfilter.h"

class Capture
{
public:
    Capture();
    int initVideo(int, const std::string);

private:
    // used for comparing videos
    double getPSNR(const cv::Mat& I1, const cv::Mat& I2);
    int lowThreshold;

    cv::Scalar getMSSIM( const cv::Mat& i1, const cv::Mat& i2);
    cv::TrackbarCallback change = 0;
    CannyFilter* cf;
    cv::VideoCapture captRefrnc;
};

#endif // CAPTURE_H
