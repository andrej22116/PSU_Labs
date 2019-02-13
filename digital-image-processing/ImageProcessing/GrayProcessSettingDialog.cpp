#include "GrayProcessSettingDialog.hpp"
#include "ui_GrayProcessSettingDialog.h"
#include "GrayProcessor.hpp"

GrayProcessSettingDialog::GrayProcessSettingDialog(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::GrayProcessSettingDialog),
    _grayProcessor(new GrayProcessor{})
{
    ui->setupUi(centralWidget);

    connect( ui->radioRed, &QRadioButton::toggled, this
           , &GrayProcessSettingDialog::on_radioRed_toggled );
    connect( ui->radioGreen, &QRadioButton::toggled, this
           , &GrayProcessSettingDialog::on_radioGreen_toggled );
    connect( ui->radioBlue, &QRadioButton::toggled, this
           , &GrayProcessSettingDialog::on_radioBlue_toggled );
    connect( ui->radioAverage, &QRadioButton::toggled, this
           , &GrayProcessSettingDialog::on_radioAverage_toggled );
    connect( ui->radioSmart, &QRadioButton::toggled, this
           , &GrayProcessSettingDialog::on_radioSmart_toggled );
}

GrayProcessSettingDialog::~GrayProcessSettingDialog()
{
    delete ui;
}

ImageProcessor GrayProcessSettingDialog::imageProcessor()
{
    return *_grayProcessor;
}

void GrayProcessSettingDialog::on_radioRed_toggled(bool checked)
{
    if ( checked ) {
        _grayProcessor->setBy(GrayProcessor::By::Red);
        updatePreviewImage();
    }
}

void GrayProcessSettingDialog::on_radioGreen_toggled(bool checked)
{
    if ( checked ) {
        _grayProcessor->setBy(GrayProcessor::By::Green);
        updatePreviewImage();
    }
}

void GrayProcessSettingDialog::on_radioBlue_toggled(bool checked)
{
    if ( checked ) {
        _grayProcessor->setBy(GrayProcessor::By::Blue);
        updatePreviewImage();
    }
}

void GrayProcessSettingDialog::on_radioAverage_toggled(bool checked)
{
    if ( checked ) {
        _grayProcessor->setBy(GrayProcessor::By::Delta);
        updatePreviewImage();
    }
}

void GrayProcessSettingDialog::on_radioSmart_toggled(bool checked)
{
    if ( checked ) {
        _grayProcessor->setBy(GrayProcessor::By::Smart);
        updatePreviewImage();
    }
}
