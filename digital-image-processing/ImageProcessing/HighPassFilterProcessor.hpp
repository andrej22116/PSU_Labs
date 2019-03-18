#ifndef HIGHPASSFILTERPROCESSOR_HPP
#define HIGHPASSFILTERPROCESSOR_HPP


#include "BaseMatrixCoreProcessor.hpp"


class HighPassFilterProcessor : public BaseMatrixCoreProcessor<int>
{
public:
    enum Mask {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    HighPassFilterProcessor(Mask mask = Mask_3x3) noexcept;
};

#endif // HIGHPASSFILTERPROCESSOR_HPP
