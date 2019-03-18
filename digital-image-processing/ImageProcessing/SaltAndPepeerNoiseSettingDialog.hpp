#ifndef SALTANDPEPEERNOISESETTINGDIALOG_HPP
#define SALTANDPEPEERNOISESETTINGDIALOG_HPP

#include "ProcessSettingDialog.hpp"

namespace Ui {
class SaltAndPepeerNoiseSettingDialog;
}

class SaltAndPapeerNoiseProcessor;

class SaltAndPepeerNoiseSettingDialog : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit SaltAndPepeerNoiseSettingDialog(QWidget *parent = nullptr);
    ~SaltAndPepeerNoiseSettingDialog() override;

    ImageProcessor imageProcessor() override;

private slots:
    void on_trasholdChanceSlider_valueChanged(int value);

private:
    Ui::SaltAndPepeerNoiseSettingDialog *ui;
    std::unique_ptr<SaltAndPapeerNoiseProcessor> _saltAndPapeerNoiseProcessor;
};

#endif // SALTANDPEPEERNOISESETTINGDIALOG_HPP
