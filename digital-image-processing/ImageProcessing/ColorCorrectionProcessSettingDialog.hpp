#ifndef COLORCORRECTIONPROCESSSETTINGDIALOG_HPP
#define COLORCORRECTIONPROCESSSETTINGDIALOG_HPP

#include "ProcessSettingDialog.hpp"

namespace Ui {
class ColorCorrectionProcessSettingDialog;
}

class ColorCorrectionProcessor;

class ColorCorrectionProcessSettingDialog : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit ColorCorrectionProcessSettingDialog(QWidget *parent = nullptr);
    ~ColorCorrectionProcessSettingDialog() override;

    ImageProcessor imageProcessor() override;

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::ColorCorrectionProcessSettingDialog *ui;
    std::unique_ptr<ColorCorrectionProcessor> _colorCorrectionProcessor;
};

#endif // COLORCORRECTIONPROCESSSETTINGDIALOG_HPP
