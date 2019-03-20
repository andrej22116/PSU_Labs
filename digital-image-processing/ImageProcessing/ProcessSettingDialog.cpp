#include "ProcessSettingDialog.hpp"
#include "ui_ProcessSettingDialog.h"

#include "ScaleProcessor.hpp"
#include "WaitAnimationOverlayWidget.hpp"

#include <QPixmap>
#include <QGridLayout>

ProcessSettingDialog::ProcessSettingDialog(QWidget *parent) :
    QDialog(parent),
    centralWidget(new QWidget(this)),
    ui(new Ui::ProcessSettingDialog)
{
    ui->setupUi(this);
    _waitAnimationOverlayWidget = new WaitAnimationOverlayWidget{ 64, ui->labelImage };

    connect( &_imageController, &ImageController::processEnded
           , this, &ProcessSettingDialog::onEndProcess );
}

ProcessSettingDialog::~ProcessSettingDialog()
{
    delete centralWidget;
    delete ui;

    _imageController.terminate();
    _imageController.wait();
}

void ProcessSettingDialog::setImage(const QImage& image)
{
    _imageController.setImage(image);
    setImage();
}

void ProcessSettingDialog::setImage(QImage&& image)
{
    _imageController.setImage(image);
    setImage();
}

void ProcessSettingDialog::updatePreviewImage()
{
    _waitAnimationOverlayWidget->showModal();
    _imageController.wait();
    _imageController.process( imageProcessor() );
}

void ProcessSettingDialog::setImage()
{
    auto image = _imageController.image();
    double scale = 1;
    auto layout = dynamic_cast<QGridLayout*>(ui->centralWidget->layout());

    if ( image->width() < image->height() ) {
        scale = static_cast<double>(IMAGE_SHORT_SIDE_LENGTH)
              / static_cast<double>(image->width());

        layout->addWidget(centralWidget, 0, 1);
    }
    else {
        scale = static_cast<double>(IMAGE_SHORT_SIDE_LENGTH)
              / static_cast<double>(image->height());

        layout->addWidget(centralWidget, 1, 0);
    }

    _imageController.process( ScaleProcessor{ scale, scale }, false );
    _imageController.apply();

    updatePreviewImage();
}

void ProcessSettingDialog::onEndProcess()
{
    _waitAnimationOverlayWidget->hideModal();
    ui->labelImage->setPixmap(QPixmap::fromImage(*_imageController.processedImage()));
    this->setFixedSize(this->minimumSizeHint());
}
