#include "GaussianBlureSetupDialog.hpp"
#include "GaussianBlureProcessor.hpp"

GaussianBlureSetupDialog::GaussianBlureSetupDialog(QWidget* parent) :
    KernelSetupWidget(parent)
{
}

ImageProcessor GaussianBlureSetupDialog::imageProcessor()
{
    switch( maskType() ) {
    case MaskType::Mask_3x3: return GaussianBlureProcessor{ GaussianBlureProcessor::Mask_3x3 };
    case MaskType::Mask_5x5: return GaussianBlureProcessor{ GaussianBlureProcessor::Mask_5x5 };
    case MaskType::Mask_7x7: return GaussianBlureProcessor{ GaussianBlureProcessor::Mask_7x7 };
    }
}
