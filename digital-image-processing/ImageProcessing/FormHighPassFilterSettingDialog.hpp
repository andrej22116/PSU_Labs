#ifndef FORMHIGHPASSFILTERSETTINGDIALOG_HPP
#define FORMHIGHPASSFILTERSETTINGDIALOG_HPP

#include "KernelSetupWidget.hpp"

class FormHighPassFilterSettingDialog : public KernelSetupWidget
{
    Q_OBJECT

public:
    explicit FormHighPassFilterSettingDialog(QWidget* parent = nullptr);
    ~FormHighPassFilterSettingDialog() override {}

    ImageProcessor imageProcessor() override;
};

#endif // FORMHIGHPASSFILTERSETTINGDIALOG_HPP
