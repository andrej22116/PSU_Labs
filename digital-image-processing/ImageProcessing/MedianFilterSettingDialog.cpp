#include "MedianFilterSettingDialog.hpp"
#include "MedianFilterProcessor.hpp"

MedianFilterSettingDialog::MedianFilterSettingDialog(QWidget* parent) :
    KernelSetupWidget(parent)
{
}

ImageProcessor MedianFilterSettingDialog::imageProcessor()
{
    switch( maskType() ) {
    case MaskType::Mask_3x3: return MedianFilterProcessor{ MedianFilterProcessor::Mask::Mask_3x3 };
    case MaskType::Mask_5x5: return MedianFilterProcessor{ MedianFilterProcessor::Mask::Mask_5x5 };
    case MaskType::Mask_7x7: return MedianFilterProcessor{ MedianFilterProcessor::Mask::Mask_7x7 };
    }
}
