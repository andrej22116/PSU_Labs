#include "BorderSelectionSettingDialog.hpp"
#include "BorderSelectionProcessor.hpp"

BorderSelectionSettingDialog::BorderSelectionSettingDialog(QWidget* parent) :
    KernelSetupWidget(parent)
{

}

ImageProcessor BorderSelectionSettingDialog::imageProcessor()
{
    switch( maskType() ) {
    case MaskType::Mask_3x3: return BorderSelectionProcessor{ BorderSelectionProcessor::Mask_3x3 };
    case MaskType::Mask_5x5: return BorderSelectionProcessor{ BorderSelectionProcessor::Mask_5x5 };
    case MaskType::Mask_7x7: return BorderSelectionProcessor{ BorderSelectionProcessor::Mask_7x7 };
    }
}
