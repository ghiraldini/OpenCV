#include "mainwindow.h"
#include <QApplication>
#include <QThread>

#include "imageviewer.h"
#include "converter.h"
#include "capture.h"

#include "opencv2/core/core.hpp"

class Thread final : public QThread {
public: ~Thread() {
        quit();
        wait();
    }
};

Q_DECLARE_METATYPE(cv::Mat);

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>();

    QApplication app(argc, argv);

    ImageViewer view;
    Capture capture;
    Converter converter;

    Thread captureThread,
            converterThread;

    // Everything runs at the same priority as the gui, so it won't supply useless frames.
    converter.setProcessAll(false);

    captureThread.start();
    converterThread.start();

    capture.moveToThread(&captureThread);
    converter.moveToThread(&converterThread);

    QObject::connect(&capture, &Capture::frameReady, &converter, &Converter::processFrame);
    QObject::connect(&converter, &Converter::imageReady, &view, &ImageViewer::setImage);

    view.show();

    QObject::connect(&capture, &Capture::started, [](){ qDebug() << "Capture started."; });
    QMetaObject::invokeMethod(&capture, "start");

    return app.exec();
}

//#include "main.moc"



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
