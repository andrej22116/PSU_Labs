#ifndef BASEMATRIXCOREPROCESSOR_HPP
#define BASEMATRIXCOREPROCESSOR_HPP


#define MacCloseOnRange(min, max, value)    \
        ( (value) > (max) ? (max) :         \
          (value) < (min) ? (min) :         \
          (value)                           \
        )


#include <vector>
#include <QImage>
#include <cmath>

#include <QPainter>

#include "ScaleProcessor.hpp"


template<typename T>
class BaseMatrixCoreProcessor
{
protected:
    std::vector<T> _core;
    short _coreSize;
    short _coreHalfSize;
    T _coreWeight;

public:
    BaseMatrixCoreProcessor(std::initializer_list<T> core) { init(core); }
    BaseMatrixCoreProcessor(const std::vector<T>& core) { init(core); }
    virtual ~BaseMatrixCoreProcessor() {}

    QImage operator () (const QImage& image)
    {
        _coreWeight = 0;
        for ( auto i : _core ) {
            _coreWeight += i;
        }
        if ( _coreWeight == 0 ) { _coreWeight = 1; }

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

protected:
    BaseMatrixCoreProcessor() {}

    void init(std::vector<T> core) {
        _core = std::move(core);
        _coreSize = static_cast<short>(std::sqrt(_core.size()));
        _coreHalfSize = static_cast<short>(_coreSize / 2);
    }

    virtual void rgbProcessing(const QImage& inputImage, QImage& outputImage)
    {
        auto inputBits = inputImage.bits();
        auto outputBits = outputImage.bits();

        auto width = outputImage.width();
        auto height = outputImage.height();

        auto bytesPerLine = inputImage.bytesPerLine();

        std::vector<const uchar*> maskOffsets;
        maskOffsets.reserve(_coreSize + 5);

        for ( int y = 0; y < height; ++y ) {
            maskOffsets.clear();

            for ( int coreY = 0; coreY < _coreSize; ++coreY ) {
                for ( int coreX = 0; coreX < _coreSize; ++coreX ) {
                    maskOffsets.push_back(inputBits + (bytesPerLine * (coreY + y)) + (coreX * 4));
                }
            }

            for ( int x = 0; x < width; ++x ) {
                T redComponent   = 0;
                T greenComponent = 0;
                T blueComponent  = 0;
                T alphaComponent = 0;

                for ( int i = 0, size = _core.size(); i < size; ++i ) {
                    redComponent    += static_cast<T>((*maskOffsets[i]++) * _core[i]);
                    greenComponent  += static_cast<T>((*maskOffsets[i]++) * _core[i]);
                    blueComponent   += static_cast<T>((*maskOffsets[i]++) * _core[i]);
                    alphaComponent  += static_cast<T>((*maskOffsets[i]++) * _core[i]);
                }

                redComponent   /= _coreWeight;
                greenComponent /= _coreWeight;
                blueComponent  /= _coreWeight;
                alphaComponent /= _coreWeight;

                *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(redComponent)));
                *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(greenComponent)));
                *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(blueComponent)));
                *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(alphaComponent)));
            }
        }
    }

    virtual void grayProcessing(const QImage& inputImage, QImage& outputImage)
    {
        auto inputBits = inputImage.bits();
        auto outputBits = outputImage.bits();

        auto width = outputImage.width();
        auto height = outputImage.height();

        auto bytesPerLine = inputImage.bytesPerLine();
        auto shit = outputImage.bytesPerLine() - width;

        std::vector<const uchar*> maskOffsets;
        maskOffsets.reserve(_coreSize + 5);

        for ( int y = 0; y < height; ++y ) {
            maskOffsets.clear();

            for ( int coreY = 0; coreY < _coreSize; ++coreY ) {
                for ( int coreX = 0; coreX < _coreSize; ++coreX ) {
                    maskOffsets.push_back(inputBits + (bytesPerLine * (coreY + y)) + coreX);
                }
            }

            for ( int x = 0; x < width; ++x ) {
                T grayComponent = 0;

                for ( int i = 0, size = _core.size(); i < size; ++i ) {
                    grayComponent    += static_cast<T>((*maskOffsets[i]++) * _core[i]);
                }

                *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(grayComponent)));
            }

            outputBits += shit;
        }
    }
};

#endif // BASEMATRIXCOREPROCESSOR_HPP
