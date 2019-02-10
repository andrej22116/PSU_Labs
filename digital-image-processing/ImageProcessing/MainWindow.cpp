#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "ImageController.hpp"
#include "GrayProcessor.hpp"
#include "ScaleProcessor.hpp"

#include <QImage>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui( new Ui::MainWindow ),
    _imageController( new ImageController() )
{
    ui->setupUi(this);

    _imageController->load("test.jpg");
    _imageController->process(GrayProcessor{ GrayProcessor::By::Smart });
    _imageController->apply();
    _imageController->process(ScaleProcessor{ 2, 2 });

    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->processedImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _imageController;
}
