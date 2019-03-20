#include "ContrastProcessorSettingDialog.hpp"
#include "ui_ContrastProcessorSettingDialog.h"

#include "ContrastProcessor.hpp"

ContrastProcessorSettingDialog::ContrastProcessorSettingDialog(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::ContrastProcessorSettingDialog),
    _selectedAlgorithm(0)
{
    ui->setupUi(centralWidget);

    connect(ui->radioLaplas, &QRadioButton::toggled,
            this, &ContrastProcessorSettingDialog::on_radioLaplas_toggled);
    connect(ui->radioPrevitt, &QRadioButton::toggled,
            this, &ContrastProcessorSettingDialog::on_radioPrevitt_toggled);
    connect(ui->radioRoberts, &QRadioButton::toggled,
            this, &ContrastProcessorSettingDialog::on_radioRoberts_toggled);
    connect(ui->radioSobel, &QRadioButton::toggled,
            this, &ContrastProcessorSettingDialog::on_radioSobel_toggled);
}

ContrastProcessorSettingDialog::~ContrastProcessorSettingDialog()
{
    delete ui;
}

ImageProcessor ContrastProcessorSettingDialog::imageProcessor()
{
    switch ( _selectedAlgorithm ) {
    case 0: { return ContrastProcessor{ContrastProcessor::ContrastAlgorithm::Laplas}; }
    case 1: { return ContrastProcessor{ContrastProcessor::ContrastAlgorithm::Previtt}; }
    case 2: { return ContrastProcessor{ContrastProcessor::ContrastAlgorithm::Roberts}; }
    case 3: { return ContrastProcessor{ContrastProcessor::ContrastAlgorithm::Sobel}; }
    default: { return ContrastProcessor{ContrastProcessor::ContrastAlgorithm::Sobel}; }
    }
}

void ContrastProcessorSettingDialog::on_radioLaplas_toggled(bool checked)
{
    if ( !checked ) { return; }
    _selectedAlgorithm = 0;
    updatePreviewImage();
}

void ContrastProcessorSettingDialog::on_radioPrevitt_toggled(bool checked)
{
    if ( !checked ) { return; }
    _selectedAlgorithm = 1;
    updatePreviewImage();
}

void ContrastProcessorSettingDialog::on_radioRoberts_toggled(bool checked)
{
    if ( !checked ) { return; }
    _selectedAlgorithm = 2;
    updatePreviewImage();
}

void ContrastProcessorSettingDialog::on_radioSobel_toggled(bool checked)
{
    if ( !checked ) { return; }
    _selectedAlgorithm = 3;
    updatePreviewImage();
}
