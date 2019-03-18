#include "GaussianNoiseProcessor.hpp"
#include <QImage>
#include <QDebug>

GaussianNoiseProcessor::GaussianNoiseProcessor()
{

}

QImage GaussianNoiseProcessor::operator ()(const QImage &image) noexcept
{
    QImage result { image.size(), image.format() };
    switch ( image.format() ) {
    case QImage::Format::Format_RGB32:
    case QImage::Format::Format_ARGB32: { colorNoise(image, result); } break;
    case QImage::Format::Format_Grayscale8: { grayNoise(image, result); } break;
    default: break;
    }

    return result;
}

void GaussianNoiseProcessor::colorNoise(const QImage &inputImage, QImage &outputImage) noexcept
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto inputBitsEnd = inputBits + inputImage.sizeInBytes();

    while ( inputBits != inputBitsEnd ) {
        short noise = static_cast<short>(255.0 * _distribution(_generator));
        short r = (*inputBits++) + noise;
        short g = (*inputBits++) + noise;
        short b = (*inputBits++) + noise;
        *outputBits++ = r > 255 ? 255u : ( r < 0 ? 0 : static_cast<uchar>(r) );
        *outputBits++ = g > 255 ? 255u : ( g < 0 ? 0 : static_cast<uchar>(g) );
        *outputBits++ = b > 255 ? 255u : ( b < 0 ? 0 : static_cast<uchar>(b) );
        *outputBits++ = *inputBits++;
    }
}

void GaussianNoiseProcessor::grayNoise(const QImage &inputImage, QImage &outputImage) noexcept
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto inputBitsEnd = inputBits + inputImage.sizeInBytes();

    while ( inputBits != inputBitsEnd ) {
        short colorWithNoise = *inputBits++ + static_cast<short>(255.0 * _distribution(_generator));
        *outputBits++ = colorWithNoise > 255 ? 255u : (
                        colorWithNoise < 0 ? 0 : static_cast<uchar>(colorWithNoise) );
    }
}
