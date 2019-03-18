#ifndef MEDIANFILTERSETTINGDIALOG_HPP
#define MEDIANFILTERSETTINGDIALOG_HPP


#include "KernelSetupWidget.hpp"


class MedianFilterSettingDialog : public KernelSetupWidget
{
    Q_OBJECT

public:
    explicit MedianFilterSettingDialog(QWidget* parent = nullptr);
    ~MedianFilterSettingDialog() override {}

    ImageProcessor imageProcessor() override;
};

#endif // MEDIANFILTERSETTINGDIALOG_HPP
