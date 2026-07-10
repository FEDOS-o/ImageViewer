#pragma once

#include <QObject>
#include <QImage>
#include <QString>
#include <QPointF>

class ImageModel : public QObject {
    Q_OBJECT
public:
    explicit ImageModel(QObject *parent = nullptr);

    // Пустые методы-заглушки
    bool loadImage(const QString &filePath) { return false; }
    void setScale(double scale) {}
    void setOffset(const QPointF &offset) {}
    void resetTransform() {}

    // Геттеры-заглушки
    const QImage& getImage() const { return m_image; }
    const QString& getFilePath() const { return m_filePath; }
    double getScale() const { return 1.0; }
    const QPointF& getOffset() const { return m_offset; }
    QSize getImageSize() const { return QSize(0, 0); }
    bool hasImage() const { return false; }

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