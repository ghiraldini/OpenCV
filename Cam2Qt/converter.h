#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QBasicTimer>
#include <QImage>
#include <QWidget>
#include <QDebug>
#include <QTimerEvent>

#include <iostream>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>


/*
 * The Converter class converts the incoming frame to a scaled-down
 * QImage user property. It notifies of the image update.
 * The image is retained to prevent memory reallocations.
 * The processAll property selects whether all frames will
 * be converted, or only the most recent one should more than one get queued up.
 */


class Converter : public QObject {    
    Q_OBJECT
    Q_PROPERTY(QImage image READ image NOTIFY imageReady USER true)
    Q_PROPERTY(bool processAll READ processAll WRITE setProcessAll)

private:
    QBasicTimer m_timer;
    cv::Mat m_frame;
    QImage m_image;
    bool m_processAll = true;
    int drops;

    void queue(const cv::Mat &frame);
    void process(const cv::Mat &frame);
    void timerEvent(QTimerEvent *ev);

public:
    Converter(QObject * parent = nullptr) : QObject(parent) { drops = 0; }
    ~Converter() {}
    bool processAll() const;
    void setProcessAll(bool);
    QImage image() const { return m_image; }

public slots:
    Q_SLOT void processFrame(const cv::Mat &frame);

signals:
    Q_SIGNAL void imageReady(const QImage &);
};

#endif // CONVERTER_H
