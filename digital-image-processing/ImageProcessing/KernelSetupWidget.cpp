#include "KernelSetupWidget.hpp"
#include "ui_CoreSetupWidget.h"

KernelSetupWidget::KernelSetupWidget(QWidget *parent) :
    ProcessSettingDialog(parent),
    ui(new Ui::CoreSetupWidget{}),
    _maskType(MaskType::Mask_3x3)
{
    ui->setupUi(centralWidget);

    connect(ui->radio_3x3, &QRadioButton::toggled,
            this, &KernelSetupWidget::selectKernel_3x3);
    connect(ui->radio_5x5, &QRadioButton::toggled,
            this, &KernelSetupWidget::selectKernel_5x5);
    connect(ui->radio_7x7, &QRadioButton::toggled,
            this, &KernelSetupWidget::selectKernel_7x7);
}

KernelSetupWidget::~KernelSetupWidget()
{
    delete ui;
}

void KernelSetupWidget::selectKernel_3x3(bool selected)
{
    if ( !selected ) { return; }

    _maskType = MaskType::Mask_3x3;
    updatePreviewImage();
}

void KernelSetupWidget::selectKernel_5x5(bool selected)
{
    if ( !selected ) { return; }

    _maskType = MaskType::Mask_5x5;
    updatePreviewImage();
}

void KernelSetupWidget::selectKernel_7x7(bool selected)
{
    if ( !selected ) { return; }

    _maskType = MaskType::Mask_7x7;
    updatePreviewImage();
}

KernelSetupWidget::MaskType KernelSetupWidget::maskType()
{
    return _maskType;
}

