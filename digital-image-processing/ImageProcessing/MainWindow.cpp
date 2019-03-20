#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "ImageController.hpp"
#include "WaitAnimationOverlayWidget.hpp"

#include "ScaleSettingDialog.hpp"
#include "GrayProcessSettingDialog.hpp"
#include "BinaryProcessSettingDialog.hpp"
#include "SaltAndPepeerNoiseSettingDialog.hpp"
#include "ColorCorrectionProcessSettingDialog.hpp"
#include "FormHighPassFilterSettingDialog.hpp"
#include "GaussianBlureSetupDialog.hpp"
#include "EmbossProcessorSettingDialog.hpp"
#include "BorderSelectionSettingDialog.hpp"
#include "LowPassFilterSettingDialog.hpp"
#include "MedianFilterSettingDialog.hpp"
#include "ContrastProcessorSettingDialog.hpp"

#include "GaussianNoiseProcessor.hpp"

#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui( new Ui::MainWindow ),
    _imageController( new ImageController() ),
    _labelPath(new QLabel(this)),
    _labelSize(new QLabel(this))
{
    ui->setupUi(this);
    ui->statusBar->addWidget(_labelSize);
    ui->statusBar->addPermanentWidget(_labelPath);

    connect( _imageController, &ImageController::processEnded
           , this, &MainWindow::onEndProcess );

    _waitAnimationOverlayWidget = new WaitAnimationOverlayWidget(128, ui->centralWidget);

    disableAllActions();
    ui->actionOpen->setEnabled(true);

    ui->actionExit->setShortcut(Qt::ALT | Qt::Key_F4);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _imageController;
    delete _labelPath;
    delete _labelSize;

    _imageController->terminate();
    _imageController->wait();
}

void MainWindow::runProcessDialog(ProcessSettingDialog& dialog)
{
    dialog.setImage(*_imageController->image());
    if ( dialog.exec() != QDialog::DialogCode::Accepted ) {
        return;
    }

    disableAllActions();
    _waitAnimationOverlayWidget->showModal();
    _imageController->process(dialog.imageProcessor());
}

void MainWindow::openImage()
{
    if ( _savePath.isEmpty() ) {
        return;
    }

    _imageController->load(_savePath);
    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->image()));

    enableAllActions();
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    _labelPath->setText(_savePath);
    _labelSize->setText( QString{ "%2x%3" }
                         .arg(_imageController->image()->width())
                         .arg(_imageController->image()->height()) );
}

void MainWindow::disableAllActions()
{
    disableAllAlgorithmActions();

    ui->actionOpen->setDisabled(true);
    ui->actionSave->setDisabled(true);
    ui->actionSaveAs->setDisabled(true);
}

void MainWindow::enableAllActions()
{
    enableAllAlgorithmActions();

    ui->actionOpen->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSaveAs->setEnabled(true);
}

void MainWindow::disableAllAlgorithmActions()
{
    ui->menuNoise->setDisabled(true);
    ui->menuFilter->setDisabled(true);
    ui->menuModify->setDisabled(true);
    ui->menuEdit->setDisabled(true);
}

void MainWindow::enableAllAlgorithmActions()
{
    ui->menuNoise->setEnabled(true);
    ui->menuFilter->setEnabled(true);
    ui->menuModify->setEnabled(true);
    ui->menuEdit->setEnabled(true);
}

void MainWindow::onEndProcess()
{
    _imageController->apply();
    ui->imageLabel->setPixmap(QPixmap::fromImage(*_imageController->image()));
    _waitAnimationOverlayWidget->hideModal();

    enableAllActions();
    updateStatusBar();
}

void MainWindow::on_actionGray_triggered()
{
    GrayProcessSettingDialog dialog(this);
    runProcessDialog(dialog);
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

    if ( QFile::exists(_savePath) ) {
        auto reply = QMessageBox::question( this, "Сохранение", "Файл уже существует. Перезаписать его?"
                                          , QMessageBox::Yes | QMessageBox::No);
        if ( reply != QMessageBox::Ok ) {
            return;
        }
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

    if ( QFile::exists(_savePath) ) {
        auto reply = QMessageBox::question( this, "Сохранение", "Файл уже существует. Перезаписать его?"
                                          , QMessageBox::Yes | QMessageBox::No);
        if ( reply != QMessageBox::Ok ) {
            return;
        }
    }

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
    EmbossProcessorSettingDialog dialog{ this };
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

void MainWindow::on_actionScale_triggered()
{
    ScaleSettingDialog dialog{ _imageController->image()->width()
                             , _imageController->image()->height()
                             , this };
    if ( dialog.exec() != QDialog::DialogCode::Accepted ) {
        return;
    }

    disableAllActions();
    _waitAnimationOverlayWidget->showModal();
    _imageController->process(dialog.imageProcessor());
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionContrast_triggered()
{
    ContrastProcessorSettingDialog dialog{ this };
    runProcessDialog(dialog);
}
