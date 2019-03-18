#include "LowPassFilterSettingDialog.hpp"
#include "LowPassFilterProcessor.hpp"

LowPassFilterSettingDialog::LowPassFilterSettingDialog(QWidget* parent) :
    KernelSetupWidget(parent)
{
}

ImageProcessor LowPassFilterSettingDialog::imageProcessor()
{
    switch( maskType() ) {
    case MaskType::Mask_3x3: return LowPassFilterProcessor{ LowPassFilterProcessor::Mask_3x3 };
    case MaskType::Mask_5x5: return LowPassFilterProcessor{ LowPassFilterProcessor::Mask_5x5 };
    case MaskType::Mask_7x7: return LowPassFilterProcessor{ LowPassFilterProcessor::Mask_7x7 };
    }
}
