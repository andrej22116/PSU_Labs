#include "SaltAndPepeerNoiseSettingDialog.hpp"
#include "ui_SaltAndPepeerNoiseSettingDialog.h"

#include "SaltAndPapeerNoiseProcessor.hpp"

SaltAndPepeerNoiseSettingDialog::SaltAndPepeerNoiseSettingDialog(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::SaltAndPepeerNoiseSettingDialog),
    _saltAndPapeerNoiseProcessor(new SaltAndPapeerNoiseProcessor{})
{
    ui->setupUi(centralWidget);

    connect(ui->trasholdChanceSlider, &QSlider::valueChanged,
            this, &SaltAndPepeerNoiseSettingDialog::on_trasholdChanceSlider_valueChanged);
}

SaltAndPepeerNoiseSettingDialog::~SaltAndPepeerNoiseSettingDialog()
{
    delete ui;
}

ImageProcessor SaltAndPepeerNoiseSettingDialog::imageProcessor()
{
    return *_saltAndPapeerNoiseProcessor;
}

void SaltAndPepeerNoiseSettingDialog::on_trasholdChanceSlider_valueChanged(int value)
{
    _saltAndPapeerNoiseProcessor->setTresholdChance(static_cast<ushort>(value));
    updatePreviewImage();
}
