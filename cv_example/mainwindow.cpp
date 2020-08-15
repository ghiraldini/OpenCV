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
    vid->initVideo(-90, getIPcam());
//    vid->BackgroundSubtract(-90, getIPcam());

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

    cv::cvtColor(image, bw, cv::COLOR_BayerBG2GRAY);
    std::cout << cv::countNonZero(bw) << std::endl;

    // show the image on window
    if( !image.empty() )
        cv::imshow("My Image", bw);



}

std::string MainWindow::getIPcam(){
    return "rtsp://admin:hodrumet999@192.168.1.116:554/cam/realmonitor?channel=1&subtype=1";

    std::string camFile = "";
    std::string camURL, line;
    std::ifstream in;
    in.open(camFile.c_str());
    if(!in) std::cout << "Failed to get cam string!" << std::endl;
    std::getline(in, line);
    camURL = line;
    return camURL;
}
