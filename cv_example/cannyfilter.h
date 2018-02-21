#ifndef CANNYFILTER_H
#define CANNYFILTER_H

#include <QObject>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>

class CannyFilter
{
public:
    CannyFilter();

    cv::Mat src, src_gray;
    cv::Mat dst, detected_edges;

    int edgeThresh = 1;
    int lowThreshold;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;
    std::string window_name = "Edge Map";
    cv::TrackbarCallback change = 0;


    void* CannyThreshold(int, void *);
    void useCannyFilter(std::string image);

    cv::Mat CannyThreshold(int);
    cv::Mat useCannyFilter(cv::Mat src, int threshold);

};

#endif // CANNYFILTER_H
