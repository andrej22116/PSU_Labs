#include "EmbossProcessorSettingDialog.hpp"
#include "ui_EmbossProcessorSettingDialog.h"

#include "EmbossProcessor.hpp"

EmbossProcessorSettingDialog::EmbossProcessorSettingDialog(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::EmbossProcessorSettingDialog)
{
    ui->setupUi(centralWidget);

    connect( ui->dial, &QDial::valueChanged,
             this, &EmbossProcessorSettingDialog::on_dial_valueChanged );
}

EmbossProcessorSettingDialog::~EmbossProcessorSettingDialog()
{
    delete ui;
}

ImageProcessor EmbossProcessorSettingDialog::imageProcessor()
{
    return EmbossProcessor{ ui->dial->value() };
}

void EmbossProcessorSettingDialog::on_dial_valueChanged(int value)
{
    auto matrix = EmbossProcessor::matrix(value);

    ui->edit_00->setText(QString::number(matrix[0]));
    ui->edit_01->setText(QString::number(matrix[1]));
    ui->edit_02->setText(QString::number(matrix[2]));
    ui->edit_10->setText(QString::number(matrix[3]));
    ui->edit_11->setText(QString::number(matrix[4]));
    ui->edit_12->setText(QString::number(matrix[5]));
    ui->edit_20->setText(QString::number(matrix[6]));
    ui->edit_21->setText(QString::number(matrix[7]));
    ui->edit_22->setText(QString::number(matrix[8]));
    ui->editAngle->setText(QString::number(value));

    updatePreviewImage();
}
