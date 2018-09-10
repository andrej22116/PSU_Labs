#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/ClassPaintWidget/paintscene.h"

#include <QKeyEvent>


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new PaintScene());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete) {
        ui->graphicsView->scene()->clear();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
