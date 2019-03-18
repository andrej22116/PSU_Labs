#include "FormHighPassFilterSettingDialog.hpp"
#include "ui_CoreSetupWidget.h"
#include "HighPassFilterProcessor.hpp"

FormHighPassFilterSettingDialog::FormHighPassFilterSettingDialog(QWidget *parent) :
    KernelSetupWidget(parent)
{
}

ImageProcessor FormHighPassFilterSettingDialog::imageProcessor()
{
    switch( maskType() ) {
    case MaskType::Mask_3x3: return HighPassFilterProcessor{ HighPassFilterProcessor::Mask_3x3 };
    case MaskType::Mask_5x5: return HighPassFilterProcessor{ HighPassFilterProcessor::Mask_5x5 };
    case MaskType::Mask_7x7: return HighPassFilterProcessor{ HighPassFilterProcessor::Mask_7x7 };
    }
}
