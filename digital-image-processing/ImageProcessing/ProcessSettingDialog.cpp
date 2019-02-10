#include "ProcessSettingDialog.hpp"
#include "ui_ProcessSettingDialog.h"

ProcessSettingDialog::ProcessSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessSettingDialog)
{
    ui->setupUi(this);
}

ProcessSettingDialog::~ProcessSettingDialog()
{
    delete ui;
}
