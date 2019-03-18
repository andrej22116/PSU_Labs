#ifndef LOWPASSFILTERPROCESSOR_HPP
#define LOWPASSFILTERPROCESSOR_HPP


#include "BaseMatrixCoreProcessor.hpp"


class LowPassFilterProcessor : public BaseMatrixCoreProcessor<int>
{
public:
    enum Mask {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    LowPassFilterProcessor(Mask mask = Mask_3x3) noexcept;
};

#endif // LOWPASSFILTERPROCESSOR_HPP
