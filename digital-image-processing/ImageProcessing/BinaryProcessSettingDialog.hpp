#ifndef BINARYPROCESSSETTINGDIALOG_HPP
#define BINARYPROCESSSETTINGDIALOG_HPP

#include "ProcessSettingDialog.hpp"

namespace Ui {
class BinaryProcessSettingDialog;
}


class BinaryProcessor;


class BinaryProcessSettingDialog : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit BinaryProcessSettingDialog(QWidget *parent = nullptr);
    ~BinaryProcessSettingDialog() override;

    ImageProcessor imageProcessor() override;

private slots:
    void on_radioBase_toggled(bool checked);

    void on_radioBaseInvert_toggled(bool checked);

    void on_radioOtsu_toggled(bool checked);

    void on_radioBradleyAndRot_toggled(bool checked);

    void on_radioBaseMethod_toggled(bool checked);

private:
    Ui::BinaryProcessSettingDialog *ui;
    std::unique_ptr<BinaryProcessor> _binaryProcessor;
};

#endif // BINARYPROCESSSETTINGDIALOG_HPP
