#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cannyfilter.h"
#include "contour.h"
#include "capture.h"
#include "fstream"
#include "iostream"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CannyFilter* cf;
    Contour* ct;
    Capture* vid;

    void readImage(std::string image);

    //    std::string filename = "C://Users/usjaghi41/Documents/Software/Builds/cv_example/release/Desert.jpg";
    const std::string filename = "C://Users/usjaghi41/Documents/GitHub/OpenCV/cv_example/release/building.jpg";
    std::string getIPcam();
};

#endif // MAINWINDOW_H
