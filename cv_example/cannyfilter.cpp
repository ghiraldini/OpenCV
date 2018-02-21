#include "cannyfilter.h"

CannyFilter::CannyFilter()
{

}


/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
cv::Mat CannyFilter::CannyThreshold(int lt)
{
    /// Reduce noise with a kernel 3x3
    cv::blur( src_gray, detected_edges, cv::Size(3,3) );

    /// Canny detector
    cv::Canny( detected_edges, detected_edges, lt, lt * ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = cv::Scalar::all(0);

    src.copyTo( dst, detected_edges);
    return dst;
}


// Overload for single image + Trackerbar
void* CannyFilter::CannyThreshold(int lt, void*)
{
    /// Reduce noise with a kernel 3x3
    cv::blur( src_gray, detected_edges, cv::Size(3,3) );

    /// Canny detector
    cv::Canny( detected_edges, detected_edges, lt, lt * ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = cv::Scalar::all(0);

    src.copyTo( dst, detected_edges);
    cv::imshow( window_name, dst );

    return 0;
}


void CannyFilter::useCannyFilter(std::string image){

    /// Load an image
    src = cv::imread( image );
    if( !src.data )
        return;

    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );

    /// Create a window
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE );

    // Click ESC to exit
    while(cv::waitKey(33) != 27){
        /// Create a Trackbar for user to enter threshold
        cv::createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, change, CannyThreshold(0,0) );
        /// Show the image
        CannyThreshold(lowThreshold,0);
    }
    exit(0);

}



cv::Mat CannyFilter::useCannyFilter(cv::Mat src_,int threshold){
    src = src_;
    lowThreshold = threshold;
    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
    return CannyThreshold(lowThreshold);

}
