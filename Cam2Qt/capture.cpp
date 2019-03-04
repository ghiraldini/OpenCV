#include "capture.h"

Capture::Capture( std::string ip, QObject */*parent*/) {
    ip_ = ip;
}

void Capture::start(int cam) {
    if (!m_videoCapture){
        if(cam)
            m_videoCapture.reset( new cv::VideoCapture(cam) );
        else
            m_videoCapture.reset( new cv::VideoCapture(ip_) );
    }

    if (m_videoCapture->isOpened()) {
        m_timer.start(0, this);
        emit started();
    }
}

void Capture::stop() {
    m_timer.stop();
}

cv::Mat Capture::frame() const {
    return m_frame;
}

void Capture::timerEvent(QTimerEvent * ev) {
    if (ev->timerId() != m_timer.timerId()){
        return;
    }

    // Blocks until a new frame is ready
    if (!m_videoCapture->read(m_frame)) {
        m_timer.stop();
        return;
    }
    emit frameReady(m_frame);
}
