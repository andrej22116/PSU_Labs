#include "MedianFilterProcessor.hpp"
#include "ScaleProcessor.hpp"

#include <QImage>
#include <QPainter>

#include <algorithm>
#include <vector>

struct Color {
    uchar alpha;
    uchar red;
    uchar green;
    uchar blue;


    uchar intensity() const {
        return static_cast<uchar>(
                      static_cast<double>(red) * 0.299
                    + static_cast<double>(green) * 0.587
                    + static_cast<double>(blue) * 0.114
               );
    }
};

MedianFilterProcessor::MedianFilterProcessor(Mask mask) :
    _mask(mask)
{
    switch ( mask ) {
    case Mask::Mask_3x3: {
        _coreSize = 3;
        _coreHalfSize = 1;
        break;
    }
    case Mask::Mask_5x5: {
        _coreSize = 5;
        _coreHalfSize = 2;
        break;
    }
    case Mask::Mask_7x7: {
        _coreSize = 7;
        _coreHalfSize = 3;
        break;
    }
    }
}

QImage MedianFilterProcessor::operator () (const QImage& image)
{
    double scaleWidth = static_cast<double>(image.width() + _coreSize)
                      / static_cast<double>(image.width());
    double scaleHeight = static_cast<double>(image.height() + _coreSize)
                       / static_cast<double>(image.height());

    QImage scaledSource = ScaleProcessor{ scaleWidth, scaleHeight }(image);
    {
        QPainter painter { &scaledSource };
        painter.drawImage(QPoint{_coreHalfSize, _coreHalfSize}, image);
        painter.end();
    }

    QImage result { image.size(), image.format() };

    switch ( image.format() ) {
    case QImage::Format::Format_RGB32:
    case QImage::Format::Format_ARGB32: { rgbProcessing(scaledSource, result); } break;
    case QImage::Format::Format_Grayscale8: { grayProcessing(scaledSource, result); } break;
    default: break;
    }

    return result;
}

void MedianFilterProcessor::rgbProcessing(const QImage& inputImage, QImage& outputImage)
{
    auto inputBits = reinterpret_cast<const Color*>(inputImage.bits());
    auto outputBits = reinterpret_cast<Color*>(outputImage.bits());

    auto inputWidth = inputImage.width();
    auto outputWidth = outputImage.width();
    auto outputHeight = outputImage.height();

    std::vector<const Color*> maskOffsets;
    maskOffsets.reserve(static_cast<size_t>(_coreSize + 5));

    std::vector<Color> capturedPixels;
    capturedPixels.reserve(static_cast<size_t>(_coreSize + 5));

    for ( int y = 0; y < outputHeight; ++y ) {
        maskOffsets.clear();

        for ( int coreY = 0; coreY < _coreSize; ++coreY ) {
            for ( int coreX = 0; coreX < _coreSize; ++coreX ) {
                auto offset = inputBits + (inputWidth * (coreY + y)) + coreX;
                maskOffsets.push_back(offset);
                capturedPixels.push_back(*offset);
            }
        }

        for ( int x = 0; x < outputWidth; ++x ) {
            capturedPixels.clear();
            for ( auto& offset : maskOffsets) {
                capturedPixels.push_back(*offset++);
            }

            std::sort(capturedPixels.begin(), capturedPixels.end(), [](const Color& left, const Color& right) {
                return left.intensity() > right.intensity();
            });

            *outputBits++ = capturedPixels[static_cast<size_t>(_coreHalfSize + 1)];
        }
    }
}

void MedianFilterProcessor::grayProcessing(const QImage& inputImage, QImage& outputImage)
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto bytesPerLine = inputImage.bytesPerLine();
    auto garbage = outputImage.bytesPerLine() - outputImage.width();
    auto outputWidth = outputImage.width();
    auto outputHeight = outputImage.height();

    std::vector<const uchar*> maskOffsets;
    maskOffsets.reserve(static_cast<size_t>(_coreSize + 5));

    std::vector<uchar> capturedPixels;
    capturedPixels.reserve(static_cast<size_t>(_coreSize + 5));

    for ( int y = 0; y < outputHeight; ++y ) {
        maskOffsets.clear();

        for ( int coreY = 0; coreY < _coreSize; ++coreY ) {
            for ( int coreX = 0; coreX < _coreSize; ++coreX ) {
                auto offset = inputBits + (bytesPerLine * (coreY + y)) + coreX;
                maskOffsets.push_back(offset);
                capturedPixels.push_back(*offset);
            }
        }

        for ( int x = 0; x < outputWidth; ++x ) {
            capturedPixels.clear();
            for ( auto& offset : maskOffsets) {
                capturedPixels.push_back(*offset++);
            }

            std::sort(capturedPixels.begin(), capturedPixels.end());

            *outputBits++ = capturedPixels[static_cast<size_t>(_coreHalfSize + 1)];
        }

        outputBits += garbage;
    }
}
