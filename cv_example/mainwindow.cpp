#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vid = new Capture;
    vid->initVideo(0, cam);



    /* Boxes and Circles around Contours */
//    ct = new Contour;
//    ct->createContour(filename);



    /* Canny Filter (ie Edge Detection) */
//    cf = new CannyFilter;
//    cf->useCannyFilter(filename);


    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Load and Display Image
void MainWindow::readImage(std::string filename){

    // read an image
    cv::Mat image = cv::imread(filename, 1);

    // create image window named "My Image"
    cv::namedWindow("My Image");

    // show the image on window
    if( !image.empty() )
        cv::imshow("My Image", image);


}
