#include "ImageController.h"
#include "ImageModel.h"
#include "ImageViewport.h"

ImageController::ImageController(QObject *parent) 
    : QObject(parent) {
}

void ImageController::setModel(ImageModel *model) {
    m_model = model;
}

void ImageController::setViewport(ImageViewport *viewport) {
    m_viewport = viewport;
}