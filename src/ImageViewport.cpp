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
    m_model = model;
}

void ImageViewport::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::darkGray);
    
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, 
                     "Image Viewport\n(not implemented yet)");
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
}

void ImageViewport::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ImageViewport::dropEvent(QDropEvent *event) {
    event->acceptProposedAction();
}