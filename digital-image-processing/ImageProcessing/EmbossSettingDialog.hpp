#ifndef EMBOSSSETTINGDIALOG_HPP
#define EMBOSSSETTINGDIALOG_HPP

#include "KernelSetupWidget.hpp"

class EmbossSettingDialog : public KernelSetupWidget
{
public:
    explicit EmbossSettingDialog(QWidget* parent = nullptr);
    ~EmbossSettingDialog() override {}

    ImageProcessor imageProcessor() override;
};

#endif // EMBOSSSETTINGDIALOG_HPP
