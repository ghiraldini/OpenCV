#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QBasicTimer>
#include <QImage>
#include <QWidget>
#include <QDebug>
#include <QTimerEvent>

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
   QBasicTimer m_timer;
   cv::Mat m_frame;
   QImage m_image;
   bool m_processAll = true;
//   AddressTracker m_track;

   void queue(const cv::Mat &frame) {
      if (!m_frame.empty()) qDebug() << "Converter dropped frame!";
      m_frame = frame;
      if (! m_timer.isActive()) m_timer.start(0, this);
   }

   void process(const cv::Mat &frame) {
      Q_ASSERT(frame.type() == CV_8UC3);
//      int w = frame.cols / 3.0, h = frame.rows / 3.0;
       int w = frame.cols, h = frame.rows;
      if (m_image.size() != QSize{w,h})
         m_image = QImage(w, h, QImage::Format_RGB888);
      cv::Mat mat(h, w, CV_8UC3, m_image.bits(), m_image.bytesPerLine());
      cv::resize(frame, mat, mat.size(), 0, 0, cv::INTER_AREA);
      cv::cvtColor(mat, mat, CV_BGR2RGB);
      emit imageReady(m_image);
   }

   void timerEvent(QTimerEvent *ev) {
      if (ev->timerId() != m_timer.timerId()) return;
      process(m_frame);
      m_frame.release();
//      m_track.track(m_frame);
      m_timer.stop();
   }


public:
   Converter(QObject * parent = nullptr) : QObject(parent) {}
   ~Converter() { /*qDebug() << __FUNCTION__ << "reallocations" << m_track.reallocs;*/ }
   bool processAll() const { return m_processAll; }
   void setProcessAll(bool all) { m_processAll = all; }
   Q_SIGNAL void imageReady(const QImage &);

   QImage image() const { return m_image; }

   Q_SLOT void processFrame(const cv::Mat &frame) {
      if (m_processAll) process(frame); else queue(frame);
   }
};

#endif // CONVERTER_H
