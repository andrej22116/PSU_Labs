#include "ScaleSettingDialog.hpp"
#include "ui_ScaleSettingDialog.h"
#include <QIntValidator>

#include "ScaleProcessor.hpp"

ScaleSettingDialog::ScaleSettingDialog(int oldWidth, int oldHeight, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleSettingDialog),
    _oldWidth(oldWidth),
    _oldHeight(oldHeight)
{
    ui->setupUi(this);

    ui->editNewWidth->setValidator(new QIntValidator(1, (1 << 15) - 1, ui->editNewWidth));
    ui->editNewHeight->setValidator(new QIntValidator(1, (1 << 15) - 1, ui->editNewHeight));
}

ScaleSettingDialog::~ScaleSettingDialog()
{
    delete ui;
}

ImageProcessor ScaleSettingDialog::imageProcessor()
{
    return ScaleProcessor{
        static_cast<double>(ui->editNewWidth->text().toInt()) / static_cast<double>(_oldWidth),
        static_cast<double>(ui->editNewHeight->text().toInt()) / static_cast<double>(_oldHeight)
    };
}
