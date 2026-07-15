#pragma once

#include <QObject>
#include <QImage>
#include <QString>
#include <QPointF>

class ImageModel : public QObject {
    Q_OBJECT
public:
    explicit ImageModel(QObject *parent = nullptr);

    bool loadImage(const QString &filePath);
    void setScale(double scale);
    void setOffset(const QPointF &offset);
    void resetTransform();

    double calculateFitScale(const QSize &viewportSize) const;

    const QImage& getImage() const { return m_image; }
    const QString& getFilePath() const { return m_filePath; }
    double getScale() const { return m_scale; }
    const QPointF& getOffset() const { return m_offset; }
    QSize getImageSize() const { return m_image.size(); }
    bool hasImage() const { return !m_image.isNull(); }

    signals:
        void imageChanged();
    void transformChanged();
    void filePathChanged(const QString &path);

private:
    QImage m_image;
    QString m_filePath;
    double m_scale = 1.0;
    QPointF m_offset = {0, 0};
};