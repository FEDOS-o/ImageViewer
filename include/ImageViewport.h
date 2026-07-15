#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPointer>

class ImageModel;

class ImageViewport : public QWidget {
    Q_OBJECT
public:
    explicit ImageViewport(QWidget *parent = nullptr);

    void setModel(ImageModel *model);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    signals:
        void zoomRequested(double delta);
    void panRequested(const QPointF &delta);
    void resetRequested();
    void fileDropped(const QString &filePath);

private:
    void updatePixmap();
    QRectF getImageRect() const;


    QPointer<ImageModel> m_model;
    QPixmap m_pixmap;
    bool m_isPanning = false;
    QPoint m_lastMousePos;
};