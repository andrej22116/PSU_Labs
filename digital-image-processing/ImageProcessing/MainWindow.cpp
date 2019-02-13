#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "ImageController.hpp"

#include "GrayProcessSettingDialog.hpp"
#include "BinaryProcessSettingDialog.hpp"

#include <QImage>
#include <QPixmap>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui( new Ui::MainWindow ),
    _imageController( new ImageController() )
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _imageController;
}

void MainWindow::on_actionGray_triggered()
{
    GrayProcessSettingDialog dialog(this);
    runProcessDialog(dialog);
}

void MainWindow::runProcessDialog(ProcessSettingDialog& dialog)
{
    dialog.setImage(*_imageController->image());
    if ( dialog.exec() != QDialog::DialogCode::Accepted ) {
        return;
    }

    _imageController->process(dialog.imageProcessor());
    _imageController->apply();

    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->image()));
}

void MainWindow::openImage()
{
    if ( _savePath.isEmpty() ) {
        return;
    }

    _imageController->load(_savePath);
    //_imageController->process(GrayProcessor{ GrayProcessor::By::Smart });
    /*
    _imageController->process(ScaleProcessor{ double(300) / double(_imageController->image()->height())
                                            , double(300) / double(_imageController->image()->height()) });
    _imageController->apply();
    _imageController->process(GrayProcessor{ GrayProcessor::By::Smart });
    _imageController->apply();
    */

    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->image()));
}

void MainWindow::on_actionOpen_triggered()
{
    auto path = QFileDialog::getOpenFileName(this, "Open image", "./", "Image files (*.png *.jpg *.bmp)");
    if ( path.isEmpty() ) {
        return;
    }

    _savePath = path;
    openImage();
}

void MainWindow::on_actionSave_triggered()
{
    if ( _savePath.isEmpty() ) {
        on_actionSaveAs_triggered();
        return;
    }

    _imageController->save(_savePath);
}

void MainWindow::on_actionSaveAs_triggered()
{
    auto path = QFileDialog::getSaveFileName(this, "Open image", "./", "Image files (*.png *.jpg *.bmp)");
    if ( path.isEmpty() ) {
        return;
    }

    _savePath = path;
    _imageController->save(_savePath);
}

void MainWindow::on_actionBin_triggered()
{
    BinaryProcessSettingDialog dialog(this);
    runProcessDialog(dialog);
}
