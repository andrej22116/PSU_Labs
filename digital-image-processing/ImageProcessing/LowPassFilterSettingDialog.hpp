#ifndef LOWPASSFILTERSETTINGDIALOG_HPP
#define LOWPASSFILTERSETTINGDIALOG_HPP


#include "KernelSetupWidget.hpp"


class LowPassFilterSettingDialog : public KernelSetupWidget
{
    Q_OBJECT

public:
    explicit LowPassFilterSettingDialog(QWidget* parent = nullptr);
    ~LowPassFilterSettingDialog() override {}

    ImageProcessor imageProcessor() override;
};

#endif // LOWPASSFILTERSETTINGDIALOG_HPP
