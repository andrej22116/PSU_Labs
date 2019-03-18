#ifndef KERNELSETUPWIDGET_HPP
#define KERNELSETUPWIDGET_HPP

#include "ProcessSettingDialog.hpp"

namespace Ui {
class CoreSetupWidget;
}

class KernelSetupWidget : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit KernelSetupWidget(QWidget *parent = nullptr);
    ~KernelSetupWidget() override;

    ImageProcessor imageProcessor() override = 0;

private slots:
    void selectKernel_3x3(bool selected);
    void selectKernel_5x5(bool selected);
    void selectKernel_7x7(bool selected);

protected:
    enum class MaskType {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    MaskType maskType();

private:
    Ui::CoreSetupWidget *ui;
    MaskType _maskType;
};

#endif // KERNELSETUPWIDGET_HPP
