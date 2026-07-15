#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ImageModel.h"
#include "ImageViewport.h"
#include "ImageController.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    
    ui->setupUi(this);
    
    m_model = new ImageModel(this);
    m_viewport = new ImageViewport(this);
    m_controller = new ImageController(this);

    m_controller->setModel(m_model);
    m_controller->setViewport(m_viewport);
    m_viewport->setModel(m_model);

    setupViewport();
    setupConnections();

    updateStatusBar();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onOpenImage() {
    if (m_controller) {
        m_controller->onOpenImage();
    }
}

void MainWindow::onZoomIn() {
    if (m_controller) {
        m_controller->zoomIn();
    }
}

void MainWindow::onZoomOut() {
    if (m_controller) {
        m_controller->zoomOut();
    }
}

void MainWindow::onResetView() {
    if (m_controller) {
        m_controller->resetView();
    }
}

void MainWindow::updateStatusBar() {
    if (!m_model || !m_model->hasImage()) {
        ui->statusbar->showMessage("No image loaded");
        return;
    }

    QString status = QString("File: %1 | Resolution: %2:%3 | Zoom: %4%")
        .arg(m_model->getFilePath())
        .arg(m_model->getImageSize().width())
        .arg(m_model->getImageSize().height())
        .arg(m_model->getScale() * 100, 0, 'f', 1);

    ui->statusbar->showMessage(status);
}

void MainWindow::setupViewport() {
    ui->viewportLayout->addWidget(m_viewport);
}

void MainWindow::setupConnections() {
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenImage);
    connect(ui->actionZoomIn, &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui->actionZoomOut, &QAction::triggered, this, &MainWindow::onZoomOut);
    connect(ui->actionReset, &QAction::triggered, this, &MainWindow::onResetView);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);

    connect(m_model, &ImageModel::imageChanged, this, [this]() {
        if (m_model && m_model->hasImage() && m_viewport) {
            QSize viewportSize = m_viewport->size();
            double fitScale = m_model->calculateFitScale(viewportSize);
            m_model->setScale(fitScale);
            m_model->setOffset({0, 0});
        }
        updateStatusBar();
    });
    connect(m_model, &ImageModel::transformChanged, this, &MainWindow::updateStatusBar);
}