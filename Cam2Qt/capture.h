#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

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
   cv::Mat m_frame;
   QBasicTimer m_timer;
   QScopedPointer<cv::VideoCapture> m_videoCapture;
//   AddressTracker m_track;
public:
   Capture(QObject *parent = {}) : QObject(parent) {}

   ~Capture() { /*qDebug() << __FUNCTION__ << "reallocations" << m_track.reallocs;*/ }
   Q_SIGNAL void started();
   Q_SLOT void start(int cam = {}) {
      if (!m_videoCapture)
         m_videoCapture.reset(new cv::VideoCapture(cam));
      if (m_videoCapture->isOpened()) {
         m_timer.start(0, this);
         emit started();
      }
   }
   Q_SLOT void stop() { m_timer.stop(); }
   Q_SIGNAL void frameReady(const cv::Mat &);
   cv::Mat frame() const { return m_frame; }
private:
   void timerEvent(QTimerEvent * ev) {
      if (ev->timerId() != m_timer.timerId()) return;
      if (!m_videoCapture->read(m_frame)) { // Blocks until a new frame is ready
         m_timer.stop();
         return;
      }
//      m_track.track(m_frame);
      emit frameReady(m_frame);
   }
};




#endif // CAPTURE_H
