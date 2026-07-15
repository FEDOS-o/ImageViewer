#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPointer>
#include <atomic>

class ImageModel;

class ImageViewport : public QWidget {
    Q_OBJECT
public:
    explicit ImageViewport(QWidget *parent = nullptr);
    ~ImageViewport();

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
    void performUpdate(uint64_t requestVersion);
    void applyResult(uint64_t requestVersion, const QPixmap& pixmap);

    QPointer<ImageModel> m_model;
    QPixmap m_pixmap;
    QPixmap m_renderedPixmap;
    bool m_isPanning = false;
    QPoint m_lastMousePos;

    std::atomic<uint64_t> m_updateRequestVersion{0};
    int m_currentQualityLevel = 0;

    static constexpr double MIN_SCALE = 0.001;
    static constexpr double MAX_SCALE = 5.0;
    static constexpr int QUALITY_LEVELS[] = {16, 8, 4, 2, 1};
    static constexpr int MAX_QUALITY_LEVEL = 5;
};