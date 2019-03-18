#ifndef BORDERSELECTIONPROCESSOR_HPP
#define BORDERSELECTIONPROCESSOR_HPP


#include "BaseMatrixCoreProcessor.hpp"


class BorderSelectionProcessor : public BaseMatrixCoreProcessor<int>
{
public:
    enum Mask {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    BorderSelectionProcessor(Mask mask = Mask_3x3) noexcept;
};

#endif // BORDERSELECTIONPROCESSOR_HPP
