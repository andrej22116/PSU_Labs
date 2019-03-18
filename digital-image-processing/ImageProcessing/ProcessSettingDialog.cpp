#include "ProcessSettingDialog.hpp"
#include "ui_ProcessSettingDialog.h"

#include "ScaleProcessor.hpp"

#include <QPixmap>
#include <QGridLayout>

ProcessSettingDialog::ProcessSettingDialog(QWidget *parent) :
    QDialog(parent),
    centralWidget(new QWidget(this)),
    ui(new Ui::ProcessSettingDialog)
{
    ui->setupUi(this);
}

ProcessSettingDialog::~ProcessSettingDialog()
{
    delete centralWidget;
    delete ui;
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
    _imageController.process( imageProcessor() );
    ui->labelImage->setPixmap(QPixmap::fromImage(*_imageController.processedImage()));
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

    _imageController.process( ScaleProcessor{ scale, scale } );
    _imageController.apply();

    updatePreviewImage();

    this->setFixedSize(this->minimumSizeHint());
}
