#include "contour.h"

Contour::Contour()
{

}


void Contour::createContour(std::string filename){
    /// Load source image and convert it to gray
    src = cv::imread( filename, 1 );

    /// Convert image to gray and blur it
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
    cv::blur( src_gray, src_gray, cv::Size(3,3) );

    /// Create Window
    std::string source_window = "Source";
    cv::namedWindow( source_window, cv::WINDOW_AUTOSIZE );
    cv::imshow( source_window, src );

    // Click ESC to exit
    while(cv::waitKey(33) != 27){
        cv::createTrackbar( " Threshold:", "Source", &thresh, max_thresh, change, thresh_callback(0,0) );
        thresh_callback( 0, 0 );
    }
    exit(0);
}


void* Contour::thresh_callback(int, void *){
    cv::Mat threshold_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, cv::THRESH_BINARY );

    /// Find contours
    cv::findContours( threshold_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    std::vector<cv::Rect> boundRect( contours.size() );
    std::vector<cv::Point2f> center( contours.size() );
    std::vector<float> radius( contours.size() );

    for( unsigned int i = 0; i < contours.size(); i++ ){
        cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
        minEnclosingCircle( (cv::Mat)contours_poly[i], center[i], radius[i] );
    }


    /// Draw polygonal contour + bonding rects + circles
    cv::Mat drawing = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );

    for( unsigned int i = 0; i< contours.size(); i++ ){
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        cv::drawContours( drawing, contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
        cv::rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        cv::circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
    }

    /// Show in a window
    cv::namedWindow( "Contours", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Contours", drawing );

    return 0;

}
