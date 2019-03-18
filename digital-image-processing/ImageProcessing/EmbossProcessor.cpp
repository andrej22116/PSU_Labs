#include "EmbossProcessor.hpp"


EmbossProcessor::EmbossProcessor(Mask mask) noexcept
{
    switch( mask ) {
    case Mask_3x3: {
        init({   -1,  0,  0,
                  0,  0,  0,
                  0,  0,  1   });
    } break;
    case Mask_5x5: {
        init({   -1,  0,  0,  0,  0,
                  0, -1,  0,  0,  0,
                  0,  0,  0,  0,  0,
                  0,  0,  0,  1,  0,
                  0,  0,  0,  0,  1    });
    } break;
    case Mask_7x7: {
        init({   -1,  0,  0,  0,  0,  0,  0,
                  0, -1,  0,  0,  0,  0,  0,
                  0,  0, -1,  0,  0,  0,  0,
                  0,  0,  0,  0,  0,  0,  0,
                  0,  0,  0,  0,  1,  0,  0,
                  0,  0,  0,  0,  0,  1,  0,
                  0,  0,  0,  0,  0,  0,  1    });
    }}
}
