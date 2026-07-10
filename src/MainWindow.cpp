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
    
    setupViewport();
    setupConnections();
}

MainWindow::~MainWindow() {
    delete ui;
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
}