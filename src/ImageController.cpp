#include "ImageController.h"
#include "ImageModel.h"
#include "ImageViewport.h"
#include <QFileDialog>
#include <QMessageBox>

ImageController::ImageController(QObject *parent)
    : QObject(parent) {
}

void ImageController::setModel(ImageModel *model) {
    m_model = model;
}

void ImageController::setViewport(ImageViewport *viewport) {
    m_viewport = viewport;

    if (m_viewport) {
        connect(m_viewport, &ImageViewport::fileDropped,
            this, &ImageController::onFileDropped);
    }
}

void ImageController::onOpenImage() {
    if (!m_model) {
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Open Image",
        QString(),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif *.tiff);;All Files (*.*)"
    );

    if (!filePath.isEmpty()) {
        if (!m_model->loadImage(filePath)) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Failed to load image:\n" + filePath
                );
        }
    }
}

void ImageController::zoomIn() {
    if (!m_model || !m_model->hasImage()) return;
    double newScale = m_model->getScale() * 1.1;
    m_model->setScale(newScale);
}

void ImageController::zoomOut() {
    if (!m_model || !m_model->hasImage()) return;
    double newScale = m_model->getScale() / 1.1;
    if (newScale < 0.001) newScale = 0.001;
    m_model->setScale(newScale);
}

void ImageController::resetView() {
    if (!m_model || !m_model->hasImage()) return;

    m_model->setOffset({0, 0});

    if (m_viewport) {
        QSize viewportSize = m_viewport->size();
        double fitScale = m_model->calculateFitScale(viewportSize);
        m_model->setScale(fitScale);
    }
}

void ImageController::onZoomRequested(double delta) {
    if (!m_model || !m_model->hasImage()) return;
    double newScale = m_model->getScale() * delta;
    if (newScale < 0.001) newScale = 0.001;
    m_model->setScale(newScale);
}

void ImageController::onFileDropped(const QString &filePath) {
    if (m_model) {
        m_model->loadImage(filePath);
    }
}


