#ifndef CONTOUR_H
#define CONTOUR_H

#include <QObject>
//#include "highgui.hpp"
//#include "imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Contour
{
public:
    Contour();

    void createContour(std::string);

private:
    void *thresh_callback(int,void*);

    cv::Mat src;
    cv::Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    cv::RNG rng = 12345;

    cv::TrackbarCallback change = 0;
};

#endif // CONTOUR_H
