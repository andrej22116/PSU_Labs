#include "ColorCorrectionProcessor.hpp"
#include <QImage>
#include <stdexcept>

#define MacCloseOnRange(min, max, value)    \
        ( (value) > (max) ? (max) :         \
          (value) < (min) ? (min) :         \
          (value)                           \
        )

ColorCorrectionProcessor::ColorCorrectionProcessor(float power) :
    _power(power)
{
}

QImage ColorCorrectionProcessor::operator ()(const QImage &image) noexcept
{
    QImage result { image.size(), image.format() };
    switch ( image.format() ) {
    case QImage::Format::Format_RGB32:
    case QImage::Format::Format_ARGB32: { rgbCorrection(image, result); } break;
    case QImage::Format::Format_Grayscale8: { grayCorrection(image, result); } break;
    default: break;
    }

    return result;
}

float ColorCorrectionProcessor::power() noexcept
{
    return _power;
}

void ColorCorrectionProcessor::setPower(float power) noexcept(false)
{
    if ( power < -2.0f || power > 2.0f ) {
        throw std::out_of_range{ "Out of range -2..2!" };
    }

    _power = power;
}

void ColorCorrectionProcessor::rgbCorrection(const QImage &inputImage, QImage &outputImage) noexcept
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto inputBitsEnd = inputBits + inputImage.sizeInBytes();

    while ( inputBits != inputBitsEnd ) {
        *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, float(*inputBits) + 128 * _power ));
        ++inputBits;
        *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, float(*inputBits) + 128 * _power ));
        ++inputBits;
        *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, float(*inputBits) + 128 * _power ));
        ++inputBits;
        *outputBits++ = *inputBits++;
    }
}

void ColorCorrectionProcessor::grayCorrection(const QImage &inputImage, QImage &outputImage) noexcept
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto inputBitsEnd = inputBits + inputImage.sizeInBytes();

    while ( inputBits != inputBitsEnd ) {
        *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, float(*inputBits) + 128 * _power ));
        ++inputBits;
    }
}
