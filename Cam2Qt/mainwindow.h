#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>

#include "imageviewer.h"
#include "converter.h"
#include "capture.h"
#include "thread.h"

#include "opencv2/core/core.hpp"

Q_DECLARE_METATYPE(cv::Mat);

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
    QGridLayout * initGUI();
    std::string url_0;
    QLineEdit *le_user;
    QLineEdit *le_pw;
    QLineEdit *le_ip;
    QLineEdit *le_port;

signals:
    void start(int cam);

public slots:
    void initVideoStream();
};

#endif // MAINWINDOW_H



//Of course, since Qt provides native message dispatch and a Qt event loop by default in a QThread,
//it's a simple matter to use QObject for the capture process. Below is a complete, tested example.
//The capture, conversion and viewer all run in their own threads. Since cv::Mat is an implicitly
//shared class with atomic, thread-safe access, it's used as such.
//The converter has an option of not processing stale frames - useful if conversion is only done
//for display purposes.
//The viewer runs in the gui thread and correctly drops stale frames. There's never a reason for
//the viewer to deal with stale frames.
//If you were to collect data to save to disk, you should run the capture thread at high priority.
// You should also inspect OpenCV apis to see if there's a way of dumping the native camera data to disk.
//To speed up conversion, you could use the gpu-accelerated classes in OpenCV.
//The example below makes sure that in none of the memory is reallocated unless necessary for a copy:
// the Capture class maintains its own frame buffer that is reused for each subsequent frame, so does the Converter, and so does the ImageViewer.
//There are two deep copies of image data made (besides whatever happens internally in cv::VideoCatprure::read):
//The copy to the Converter's QImage.
//The copy to ImageViewer's QImage.
//Both copies are needed to assure decoupling between the threads and prevent data reallocation due to the need to detach a cv::Mat or QImage that has the reference count higher than 1. On modern architectures, memory copies are very fast.
//Since all image buffers stay in the same memory locations, their performance is optimal - they stay paged in and cached.
