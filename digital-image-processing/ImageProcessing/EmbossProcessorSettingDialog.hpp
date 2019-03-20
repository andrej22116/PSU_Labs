#ifndef EMBOSSPROCESSORSETTINGDIALOG_HPP
#define EMBOSSPROCESSORSETTINGDIALOG_HPP

#include <ProcessSettingDialog.hpp>

namespace Ui {
class EmbossProcessorSettingDialog;
}

class EmbossProcessorSettingDialog : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit EmbossProcessorSettingDialog(QWidget *parent = nullptr);
    ~EmbossProcessorSettingDialog();

    ImageProcessor imageProcessor() override;

private slots:
    void on_dial_valueChanged(int value);

private:
    Ui::EmbossProcessorSettingDialog *ui;
};

#endif // EMBOSSPROCESSORSETTINGDIALOG_HPP
