#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include <QImage>
#include <QWidget>
#include <QTimerEvent>
#include <QPainter>
#include <QDebug>

#include <iostream>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>
/*
 * The ImageViewer widget is the equivalent of a QLabel storing a pixmap.
 * The image is the user property of the viewer.
 * The incoming image is deep-copied into the user property, to prevent memory reallocations
 */

class ImageViewer : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage USER true)

private:
    bool painted = true;
    QImage m_img;
    int drops;
    void paintEvent(QPaintEvent *);

public:
    ImageViewer(QWidget * parent = nullptr) : QWidget(parent) {drops = 0;}
    ~ImageViewer() {}
    QImage image() const { return m_img; }

public slots:
    Q_SLOT void setImage(const QImage &img);

};

#endif // IMAGEVIEWER_H
