#include "ColorCorrectionProcessSettingDialog.hpp"
#include "ui_ColorCorrectionProcessSettingDialog.h"
#include "ColorCorrectionProcessor.hpp"

ColorCorrectionProcessSettingDialog::ColorCorrectionProcessSettingDialog(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::ColorCorrectionProcessSettingDialog),
    _colorCorrectionProcessor(new ColorCorrectionProcessor{})
{
    ui->setupUi(centralWidget);
    connect(ui->horizontalSlider, &QSlider::valueChanged,
            this, &ColorCorrectionProcessSettingDialog::on_horizontalSlider_valueChanged);
}

ColorCorrectionProcessSettingDialog::~ColorCorrectionProcessSettingDialog()
{
    delete ui;
}

ImageProcessor ColorCorrectionProcessSettingDialog::imageProcessor()
{
    return *_colorCorrectionProcessor;
}

void ColorCorrectionProcessSettingDialog::on_horizontalSlider_valueChanged(int value)
{
    _colorCorrectionProcessor->setPower(static_cast<float>(value) / 100.0f);
    updatePreviewImage();
}
