#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include <QImage>
#include <QWidget>
#include <QTimerEvent>
#include <QPainter>
#include <QDebug>

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
   bool painted = true;
   QImage m_img;
//   AddressTracker m_track;
   void paintEvent(QPaintEvent *) {
      QPainter p(this);
      if (!m_img.isNull()) {
         setAttribute(Qt::WA_OpaquePaintEvent);
         p.drawImage(0, 0, m_img);
         painted = true;
      }
   }
public:
   ImageViewer(QWidget * parent = nullptr) : QWidget(parent) {}
   ~ImageViewer() { /*qDebug() << __FUNCTION__ << "reallocations" << m_track.reallocs;*/ }
   Q_SLOT void setImage(const QImage &img) {
      if (!painted) qDebug() << "Viewer dropped frame!";
      if (m_img.size() == img.size() && m_img.format() == img.format()
          && m_img.bytesPerLine() == img.bytesPerLine())
         std::copy_n(img.bits(), img.sizeInBytes(), m_img.bits());
      else
         m_img = img.copy();
      painted = false;
      if (m_img.size() != size()) setFixedSize(m_img.size());
//      m_track.track(m_img);
      update();
   }
   QImage image() const { return m_img; }
};

#endif // IMAGEVIEWER_H
