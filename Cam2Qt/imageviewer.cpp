#include "imageviewer.h"

void ImageViewer::paintEvent(QPaintEvent *) {
    QPainter p(this);
    if (!m_img.isNull()) {
        setAttribute(Qt::WA_OpaquePaintEvent);
        p.drawImage(0, 0, m_img);
        painted = true;
    }
}


void ImageViewer::setImage(const QImage &img) {    
    if (!painted){
        qDebug() << "Viewer dropped frame! - COUNT: " << drops;
        drops++;
    }

    if (m_img.size() == img.size() && m_img.format() == img.format()
            && m_img.bytesPerLine() == img.bytesPerLine())
        std::copy_n(img.bits(), img.sizeInBytes(), m_img.bits());
    else
        m_img = img.copy();

    painted = false;

    if (m_img.size() != size())
        setFixedSize(m_img.size());

    update();
}
