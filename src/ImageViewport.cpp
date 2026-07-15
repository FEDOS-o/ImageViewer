#include "ImageViewport.h"
#include "ImageModel.h"
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>

ImageViewport::ImageViewport(QWidget *parent) 
    : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setMinimumSize(200, 200);
}

void ImageViewport::setModel(ImageModel *model) {
    if (m_model) {
        disconnect(m_model,nullptr,nullptr,nullptr);
    }

    m_model = model;

    if (m_model) {
        connect(m_model, &ImageModel::imageChanged, this, &ImageViewport::updatePixmap);

        connect(m_model, &ImageModel::transformChanged, this, &ImageViewport::updatePixmap);

        updatePixmap();
    }
}

void ImageViewport::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::darkGray);

    if (m_pixmap.isNull()) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter,
                         "Image Viewport\n(not implemented yet)");
        return;
    }

    QRectF imageRect = getImageRect();
    painter.drawPixmap(imageRect.topLeft(), m_pixmap);

    painter.setPen(QPen(Qt::white, 1, Qt::DashLine));
    painter.drawRect(imageRect);
}

void ImageViewport::wheelEvent(QWheelEvent *event) {
    event->accept();
}

void ImageViewport::mousePressEvent(QMouseEvent *event) {
    event->accept();
}

void ImageViewport::mouseMoveEvent(QMouseEvent *event) {
    event->accept();
}

void ImageViewport::mouseReleaseEvent(QMouseEvent *event) {
    event->accept();
}

void ImageViewport::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updatePixmap();
}

void ImageViewport::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ImageViewport::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urls = mimeData->urls();
        if (!urls.isEmpty()) {
            QString filePath = urls.first().toLocalFile();

            emit fileDropped(filePath);

            event->acceptProposedAction();
        }
    }
}

void ImageViewport::updatePixmap() {
    if (!m_model || !m_model->hasImage()) {
        m_pixmap = QPixmap();
        update();
        return;
    }

    QImage image = m_model->getImage();
    double scale = m_model->getScale();

    QSize scaledSize = image.size() * scale;

    m_pixmap = QPixmap::fromImage(image).scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    update();
}

QRectF ImageViewport::getImageRect() const {
    if (m_pixmap.isNull()) {
        return QRectF();
    }

    QSize pixmapSize = m_pixmap.size();

    QPointF offset = m_model ? m_model->getOffset() : QPointF(0, 0);

    qreal x = (width() - pixmapSize.width()) / 2.0 + offset.x();
    qreal y = (height() - pixmapSize.height()) / 2.0 + offset.y();

    return QRectF(x, y, pixmapSize.width(), pixmapSize.height());
}