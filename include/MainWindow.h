#pragma once

#include <QMainWindow>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageModel;
class ImageViewport;
class ImageController;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onOpenImage();
    void onZoomIn();
    void onZoomOut();
    void onResetView();
    void updateStatusBar();

private:
    void setupViewport();
    void setupConnections();

    Ui::MainWindow *ui;

    QPointer<ImageModel> m_model;
    QPointer<ImageViewport> m_viewport;
    QPointer<ImageController> m_controller;
};