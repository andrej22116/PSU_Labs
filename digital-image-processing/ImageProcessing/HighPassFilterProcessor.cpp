#include "HighPassFilterProcessor.hpp"

HighPassFilterProcessor::HighPassFilterProcessor(Mask mask) noexcept
{
    switch( mask ) {
    case Mask_3x3: {
        init({   -1, -1, -1,
                 -1,  9, -1,
                 -1, -1, -1   });
    } break;
    case Mask_5x5: {
        init({   -1, -1, -1, -1, -1,
                 -1,  1,  1,  1, -1,
                 -1,  1,  9,  1, -1,
                 -1,  1,  1,  1, -1,
                 -1, -1, -1, -1, -1    });
    } break;
    case Mask_7x7: {
        init({   -1, -1, -2, -2, -2, -1, -1,
                 -1,  1,  1,  1,  1,  1, -1,
                 -2,  1,  1,  2,  1,  1, -2,
                 -2,  1,  2,  9,  2,  1, -2,
                 -2,  1,  1,  2,  1,  1, -2,
                 -1,  1,  1,  1,  1,  1, -1,
                 -1, -1, -2, -2, -2, -1, -1    });
    }}
}
