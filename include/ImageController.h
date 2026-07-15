#pragma once

#include <QObject>
#include <QPointer>

class ImageModel;
class ImageViewport;

class ImageController : public QObject {
    Q_OBJECT
public:
    explicit ImageController(QObject *parent = nullptr);
    
    void setModel(ImageModel *model);
    void setViewport(ImageViewport *viewport);
    
public slots:
    void onOpenImage();
    void zoomIn();
    void zoomOut();
    void resetView();
    
private slots:
    void onZoomRequested(double delta);
    void onPanRequested(const QPointF &delta) {}
    void onResetRequested() {}
    void onFileDropped(const QString &filePath);
    
private:
    QPointer<ImageModel> m_model;
    QPointer<ImageViewport> m_viewport;
};