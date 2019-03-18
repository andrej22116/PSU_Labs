#ifndef BORDERSELECTIONSETTINGDIALOG_HPP
#define BORDERSELECTIONSETTINGDIALOG_HPP


#include "KernelSetupWidget.hpp"


class BorderSelectionSettingDialog : public KernelSetupWidget
{
    Q_OBJECT

public:
    explicit BorderSelectionSettingDialog(QWidget* parent = nullptr);
    ~BorderSelectionSettingDialog() override {}

    ImageProcessor imageProcessor() override;
};

#endif // BORDERSELECTIONSETTINGDIALOG_HPP
