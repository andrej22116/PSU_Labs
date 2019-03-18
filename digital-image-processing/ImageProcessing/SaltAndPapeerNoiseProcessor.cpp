#include "SaltAndPapeerNoiseProcessor.hpp"

#include <string>
#include <stdexcept>
#include <QImage>

SaltAndPapeerNoiseProcessor::SaltAndPapeerNoiseProcessor(ushort tresholChance) :
    _tresholdChance(tresholChance)
{
}

QImage SaltAndPapeerNoiseProcessor::operator ()(const QImage& image) noexcept
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

ushort SaltAndPapeerNoiseProcessor::tresholChance() noexcept
{
    return _tresholdChance;
}

void SaltAndPapeerNoiseProcessor::setTresholdChance(ushort tresholdChance) noexcept(false)
{
    if ( tresholdChance < MIN_TRESHHOLD_CHANCE || tresholdChance > MAX_TRESHHOLD_CHANCE ) {
        static std::string msg = "Minimum and maximum tresholds is static! Min: "
                + std::to_string(MIN_TRESHHOLD_CHANCE)
                + ", Max: "
                + std::to_string(MAX_TRESHHOLD_CHANCE)
                + "!";
        throw std::out_of_range(msg);
    }

    _tresholdChance = tresholdChance;
}

void SaltAndPapeerNoiseProcessor::colorNoise(const QImage& inputImage, QImage& outputImage) noexcept
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto inputBitsEnd = inputBits + inputImage.sizeInBytes();

    double delta = static_cast<double>(MAX_TRESHHOLD_CHANCE)
                 / static_cast<double>(MIN_TRESHHOLD_CHANCE);
    double userPrecent = static_cast<double>(_tresholdChance) * delta;

    while ( inputBits != inputBitsEnd ) {
        int randomPrecent = static_cast<int>(_distribution(_generator) * delta);
        if ( randomPrecent >= userPrecent ) {
            *outputBits++ = *inputBits++;
            *outputBits++ = *inputBits++;
            *outputBits++ = *inputBits++;
            *outputBits++ = *inputBits++;

            continue;
        }

        uchar color = static_cast<uchar>(1.0 * static_cast<double>(_distribution(_generator) * delta) * 255.0);
        color = color > 128 ? 255 : 0;

        inputBits += 3;
        *outputBits++ = color;
        *outputBits++ = color;
        *outputBits++ = color;
        *outputBits++ = *inputBits++;
    }
}

void SaltAndPapeerNoiseProcessor::grayNoise(const QImage& inputImage, QImage& outputImage) noexcept
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto inputBitsEnd = inputBits + inputImage.sizeInBytes();

    double delta = static_cast<double>(MAX_TRESHHOLD_CHANCE)
                 / static_cast<double>(MIN_TRESHHOLD_CHANCE);
    double userPrecent = static_cast<double>(_tresholdChance) * delta;

    while ( inputBits != inputBitsEnd ) {
        int randomPrecent = static_cast<int>(_distribution(_generator) * delta);
        if ( randomPrecent >= userPrecent ) {
            *outputBits++ = *inputBits++;

            continue;
        }

        uchar color = static_cast<uchar>(1.0 * static_cast<double>(_distribution(_generator) * delta) * 255.0);
        color = color > 128 ? 255 : 0;

        *outputBits++ = color;
        ++inputBits;
    }
}
