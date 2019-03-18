#include "EmbossSettingDialog.hpp"
#include "EmbossProcessor.hpp"

EmbossSettingDialog::EmbossSettingDialog(QWidget* parent) :
    KernelSetupWidget(parent)
{
}

ImageProcessor EmbossSettingDialog::imageProcessor()
{
    switch( maskType() ) {
    case MaskType::Mask_3x3: return EmbossProcessor{ EmbossProcessor::Mask_3x3 };
    case MaskType::Mask_5x5: return EmbossProcessor{ EmbossProcessor::Mask_5x5 };
    case MaskType::Mask_7x7: return EmbossProcessor{ EmbossProcessor::Mask_7x7 };
    }
}
