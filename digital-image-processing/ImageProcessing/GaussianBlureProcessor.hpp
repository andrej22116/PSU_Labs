#ifndef GAUSSIANBLUREPROCESSOR_HPP
#define GAUSSIANBLUREPROCESSOR_HPP


#include "BaseMatrixCoreProcessor.hpp"


class GaussianBlureProcessor : public BaseMatrixCoreProcessor<double>
{
public:
    enum Mask {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    GaussianBlureProcessor(Mask mask = Mask_3x3) noexcept;
};

#endif // GAUSSIANBLUREPROCESSOR_HPP
