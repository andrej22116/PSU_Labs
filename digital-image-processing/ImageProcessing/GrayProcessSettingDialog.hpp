#ifndef GRAYPROCESSSETTINGDIALOG_HPP
#define GRAYPROCESSSETTINGDIALOG_HPP

#include "ProcessSettingDialog.hpp"

namespace Ui {
class GrayProcessSettingDialog;
}

class GrayProcessor;

class GrayProcessSettingDialog : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit GrayProcessSettingDialog(QWidget *parent = nullptr);
    ~GrayProcessSettingDialog() override;

    ImageProcessor imageProcessor() override;

private slots:
    void on_radioRed_toggled(bool checked);

    void on_radioGreen_toggled(bool checked);

    void on_radioBlue_toggled(bool checked);

    void on_radioAverage_toggled(bool checked);

    void on_radioSmart_toggled(bool checked);

private:
    Ui::GrayProcessSettingDialog* ui;
    std::unique_ptr<GrayProcessor> _grayProcessor;
};

#endif // GRAYPROCESSSETTINGDIALOG_HPP
