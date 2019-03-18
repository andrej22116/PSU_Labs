#ifndef EMBOSSPROCESSOR_HPP
#define EMBOSSPROCESSOR_HPP


#include "BaseMatrixCoreProcessor.hpp"


class EmbossProcessor : public BaseMatrixCoreProcessor<int>
{
public:
    enum Mask {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    EmbossProcessor(Mask mask = Mask_3x3) noexcept;
};

#endif // EMBOSSPROCESSOR_HPP
