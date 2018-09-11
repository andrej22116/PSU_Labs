#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/ClassPaintWidget/paintscene.h"

#include <QKeyEvent>
#include <QColorDialog>


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

void MainWindow::on_menuFigureQuad_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setPaintMode(PaintScene::Square);
}

void MainWindow::on_menuFigureRect_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setPaintMode(PaintScene::Rectangle);
}

void MainWindow::on_menuFigureCircle_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setPaintMode(PaintScene::Circle);
}

void MainWindow::on_menuFigureSphere_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setPaintMode(PaintScene::Ellipse);
}

void MainWindow::on_menuFillColor_triggered()
{
    auto color = QColorDialog::getColor();
    if (!color.isValid()) { return; }
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setFillColor(color);
}

void MainWindow::on_menuFillTypeFull_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setFillMode(PaintScene::Full);
}

void MainWindow::on_menuFillTypeHorizontalLines_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setFillMode(PaintScene::HorizontalLines);
}

void MainWindow::on_menuFillTypeVerticalLines_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setFillMode(PaintScene::VerticalLines);
}

void MainWindow::on_menuAddTen_triggered()
{
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::on_menuSubTen_triggered()
{
    ui->graphicsView->scale(0.9, 0.9);
}

void MainWindow::on_menuFigureLine_triggered()
{
    dynamic_cast<PaintScene*>(ui->graphicsView->scene())->setPaintMode(PaintScene::Line);
}
