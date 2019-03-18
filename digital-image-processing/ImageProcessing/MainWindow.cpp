#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "ImageController.hpp"

#include "GrayProcessSettingDialog.hpp"
#include "BinaryProcessSettingDialog.hpp"
#include "SaltAndPepeerNoiseSettingDialog.hpp"
#include "ColorCorrectionProcessSettingDialog.hpp"
#include "FormHighPassFilterSettingDialog.hpp"
#include "GaussianBlureSetupDialog.hpp"
#include "EmbossSettingDialog.hpp"
#include "BorderSelectionSettingDialog.hpp"
#include "LowPassFilterSettingDialog.hpp"
#include "MedianFilterSettingDialog.hpp"

#include "GaussianNoiseProcessor.hpp"

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

void MainWindow::on_actionNoiseSaltAndPepper_triggered()
{
    SaltAndPepeerNoiseSettingDialog dialog(this);
    runProcessDialog(dialog);
}

void MainWindow::on_actionNoiseGause_triggered()
{
    _imageController->process(GaussianNoiseProcessor{});
    _imageController->apply();

    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->image()));
}

void MainWindow::on_actionLightCorrection_triggered()
{
    ColorCorrectionProcessSettingDialog dialog(this);
    runProcessDialog(dialog);
}

void MainWindow::on_actionStamping_triggered()
{
    EmbossSettingDialog dialog{ this };
    runProcessDialog(dialog);

    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->image()));
}

void MainWindow::on_actionFilterLL_triggered()
{
    LowPassFilterSettingDialog dialog{ this };
    runProcessDialog(dialog);
}

void MainWindow::on_actionFilterHL_triggered()
{
    FormHighPassFilterSettingDialog dialog{ this };
    runProcessDialog(dialog);
}

void MainWindow::on_actionFilterMedian_triggered()
{
    MedianFilterSettingDialog dialog{ this };
    runProcessDialog(dialog);
}

void MainWindow::on_actionBlure_triggered()
{
    GaussianBlureSetupDialog dialog{ this };
    runProcessDialog(dialog);
}

void MainWindow::on_actionBorders_triggered()
{
    BorderSelectionSettingDialog dialog{ this };
    runProcessDialog(dialog);
}
