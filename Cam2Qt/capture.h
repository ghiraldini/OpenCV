#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

#include <iostream>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>

/*
 * The Capture class fills the internal frame buffer with the captured frame.
 * It notifies of a frame change. The frame is the user property of the class.
 */


class Capture : public QObject {
    Q_OBJECT
    Q_PROPERTY(cv::Mat frame READ frame NOTIFY frameReady USER true)

private:
    cv::Mat m_frame;
    QBasicTimer m_timer;
    QScopedPointer<cv::VideoCapture> m_videoCapture;

    void timerEvent(QTimerEvent *ev);
    std::string ip_;

public:
    Capture(std::string, QObject *parent = {});
    ~Capture(){}
    cv::Mat frame() const;

public slots:
    Q_SLOT void start(int cam = {});
    Q_SLOT void stop();

signals:
    Q_SIGNAL void started();
    Q_SIGNAL void frameReady(const cv::Mat &);

};




#endif // CAPTURE_H
