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
    if (!m_model || !m_model->hasImage()) {
        event->ignore();
        return;
    }

    QPointF cursorPos = event->position();

    double currentScale = m_model->getScale();
    QPointF currentOffset = m_model->getOffset();

    double delta = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
    double newScale = currentScale * delta;
    if (newScale < 0.001) newScale = 0.001;

    QSize pixmapSize = m_pixmap.size();
    QPointF imageCenter(width() / 2.0, height() / 2.0);

    QPointF cursorDelta = cursorPos - imageCenter;

    QPointF imagePoint(
        (cursorDelta.x() - currentOffset.x()) / currentScale,
        (cursorDelta.y() - currentOffset.y()) / currentScale
    );

    QPointF newOffset(
        cursorDelta.x() - imagePoint.x() * newScale,
        cursorDelta.y() - imagePoint.y() * newScale
    );

    m_model->setScale(newScale);
    m_model->setOffset(newOffset);

    event->accept();
}

void ImageViewport::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_model && m_model->hasImage()) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        event->ignore();
    }
}

void ImageViewport::mouseMoveEvent(QMouseEvent *event) {
    if (m_isPanning) {
        QPoint delta = event->pos() - m_lastMousePos;
        emit panRequested(QPointF(delta.x(), delta.y()));
        m_lastMousePos = event->pos();
        event->accept();
    } else {
        event->ignore();
    }
}

void ImageViewport::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_isPanning) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        event->ignore();
    }
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