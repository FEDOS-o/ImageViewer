#include "ImageModel.h"

ImageModel::ImageModel(QObject *parent) 
    : QObject(parent) {
}

bool ImageModel::loadImage(const QString &filePath) {
    QImage image(filePath);

    if (image.isNull()) {
        return false;
    }

    m_image = image;
    m_filePath = filePath;

    emit imageChanged();
    emit transformChanged();
    emit filePathChanged(m_filePath);

    return true;
}

void ImageModel::setScale(double scale) {
    if (scale < 0.001) {
        return;
    }
    m_scale = scale;
    emit transformChanged();
}

void ImageModel::setOffset(const QPointF &offset) {
    m_offset = offset;
    emit transformChanged();
}

void ImageModel::resetTransform() {
    m_scale = 1.0;
    m_offset = {0, 0};
    emit transformChanged();
}

double ImageModel::calculateFitScale(const QSize &viewportSize) const {
    if (m_image.isNull() || viewportSize.isEmpty()) {
        return 1.0;
    }

    QSize imageSize = m_image.size();

    double scaleX = static_cast<double>(viewportSize.width() / imageSize.width());
    double scaleY = static_cast<double>(viewportSize.height() / imageSize.height());

    return std::min(scaleX, scaleY);
}
