#ifndef GAUSSIANBLURESETUPDIALOG_HPP
#define GAUSSIANBLURESETUPDIALOG_HPP

#include "KernelSetupWidget.hpp"

class GaussianBlureSetupDialog : public KernelSetupWidget
{
public:
    explicit GaussianBlureSetupDialog(QWidget* parent = nullptr);
    ~GaussianBlureSetupDialog() override {}

    ImageProcessor imageProcessor() override;
};

#endif // GAUSSIANBLURESETUPDIALOG_HPP
