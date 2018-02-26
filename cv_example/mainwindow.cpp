#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    readImage(filename);

    vid = new Capture;
//    vid->initVideo(-99, getIPcam());
    vid->BackgroundSubtract(0,getIPcam());

    /* Boxes and Circles around Contours */
//    ct = new Contour;
//    ct->createContour(filename);


    /* Canny Filter (ie Edge Detection) */
//    cf = new CannyFilter;
//    cf->useCannyFilter(filename);


//    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Load and Display Image
void MainWindow::readImage(std::string filename){

    // read an image
    cv::Mat image = cv::imread(filename, 1);
    cv::Mat bw = image.clone();
    // create image window named "My Image"
    cv::namedWindow("My Image");

    cv::cvtColor(image, bw, CV_BGR2GRAY);
    std::cout << cv::countNonZero(bw) << std::endl;

    // show the image on window
    if( !image.empty() )
        cv::imshow("My Image", bw);



}

std::string MainWindow::getIPcam(){
    std::string camFile = "C:/Users/usjaghi41/Documents/Personal/cam.txt";
    std::string camURL, line;
    std::ifstream in;
    in.open(camFile.c_str());
    if(!in) std::cout << "Failed to get cam string!" << std::endl;
    std::getline(in, line);
    camURL = line;
    return camURL;
}
