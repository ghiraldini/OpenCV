#include "converter.h"

void Converter::queue(const cv::Mat &frame) {
    if (!m_frame.empty()){
        qDebug() << "Converter dropped frame! - COUNT: " << drops;
        drops++;
    }

    m_frame = frame;

    if (! m_timer.isActive())
        m_timer.start(0, this);
}



void Converter::process(const cv::Mat &frame) {
    Q_ASSERT(frame.type() == CV_8UC3);
    //      int w = frame.cols / 3.0, h = frame.rows / 3.0;
//    int w = frame.cols, h = frame.rows;
//    int w = 1920, h = 1080;
    int w = 1024, h = 768;
    if (m_image.size() != QSize{w,h})
        m_image = QImage(w, h, QImage::Format_RGB888);

    cv::Mat mat(h, w, CV_8UC3, m_image.bits(), m_image.bytesPerLine());
    cv::resize(frame, mat, mat.size(), 0, 0, cv::INTER_AREA);
    cv::cvtColor(mat, mat, CV_BGR2RGB);

    emit imageReady(m_image);
}



void Converter::timerEvent(QTimerEvent *ev) {
    if (ev->timerId() != m_timer.timerId())
        return;

    process(m_frame);
    m_frame.release();
    m_timer.stop();
}

void Converter::processFrame(const cv::Mat &frame) {
    if (m_processAll) process(frame); else queue(frame);
}


bool Converter::processAll() const {
    return m_processAll;
}

void Converter::setProcessAll(bool all) {
    m_processAll = all;
}
