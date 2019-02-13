#include "BinaryProcessSettingDialog.hpp"
#include "ui_BinaryProcessSettingDialog.h"

#include "ProcessSettingDialog.hpp"
#include "BinaryProcessor.hpp"

BinaryProcessSettingDialog::BinaryProcessSettingDialog(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::BinaryProcessSettingDialog),
    _binaryProcessor(new BinaryProcessor{})
{
    ui->setupUi(centralWidget);

    connect( ui->radioBase, &QRadioButton::toggled
           , this, &BinaryProcessSettingDialog::on_radioBase_toggled);
    connect( ui->radioBaseInvert, &QRadioButton::toggled
           , this, &BinaryProcessSettingDialog::on_radioBaseInvert_toggled);
    connect( ui->radioBaseMethod, &QRadioButton::toggled
           , this, &BinaryProcessSettingDialog::on_radioBaseMethod_toggled);
    connect( ui->radioOtsu, &QRadioButton::toggled
           , this, &BinaryProcessSettingDialog::on_radioOtsu_toggled);
    connect( ui->radioBradleyAndRot, &QRadioButton::toggled
           , this, &BinaryProcessSettingDialog::on_radioBradleyAndRot_toggled);
}

BinaryProcessSettingDialog::~BinaryProcessSettingDialog()
{
    delete ui;
}

ImageProcessor BinaryProcessSettingDialog::imageProcessor()
{
    return *_binaryProcessor;
}

void BinaryProcessSettingDialog::on_radioBase_toggled(bool checked)
{
    if ( checked ) {
        _binaryProcessor->setInvert( false );
        updatePreviewImage();
    }
}

void BinaryProcessSettingDialog::on_radioBaseInvert_toggled(bool checked)
{
    if ( checked ) {
        _binaryProcessor->setInvert( true );
        updatePreviewImage();
    }
}

void BinaryProcessSettingDialog::on_radioOtsu_toggled(bool checked)
{
    if ( checked ) {
        _binaryProcessor->setMethod( BinaryProcessor::Otsu );
        updatePreviewImage();
    }
}

void BinaryProcessSettingDialog::on_radioBradleyAndRot_toggled(bool checked)
{
    if ( checked ) {
        _binaryProcessor->setMethod( BinaryProcessor::BradleyAndRot );
        updatePreviewImage();
    }
}

void BinaryProcessSettingDialog::on_radioBaseMethod_toggled(bool checked)
{
    if ( checked ) {
        _binaryProcessor->setMethod( BinaryProcessor::Base );
        updatePreviewImage();
    }
}
