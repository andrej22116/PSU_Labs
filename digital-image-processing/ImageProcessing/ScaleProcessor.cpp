#include "ScaleProcessor.hpp"
#include <stdexcept>

#include <QImage>
#include <iostream>

ScaleProcessor::ScaleProcessor( double scaleWidth
                              , double scaleHeight
                              , Method method ) :
    _scaleWidth(scaleWidth),
    _scaleHeight(scaleHeight),
    _scaleMethod(method)
{
}

QImage ScaleProcessor::operator ()(const QImage& image) noexcept(false)
{
    int width = image.width();
    int height = image.height();
    int newWidth = int( width * _scaleWidth );
    int newHeight = int( height * _scaleHeight );

    //newWidth += newWidth % 4 > 0 ? 4 - newWidth % 4 : 0;
    //newHeight += newHeight % 4 > 0 ? 4 - newWidth % 4 : 0;

    QImage newImage{ newWidth, newHeight, image.format() };

    auto inputImageBits = image.bits();
    auto outputImageBits = newImage.bits();

    switch ( image.format() ) {
    case QImage::Format::Format_Grayscale8: {
        int oldWidthGarbage = width % 4 ? 4 - (width % 4) : 0;
        int newWidthGarbage = newWidth % 4 ? 4 - (newWidth % 4) : 0;
        int oldWidthWithGarbage = width + oldWidthGarbage;
        int newWidthWithGarbage = newWidth + newWidthGarbage;

        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                int newX = int( double( x ) / _scaleWidth );
                int newY = int( double( y ) / _scaleHeight );

                outputImageBits[ y * newWidthWithGarbage + x ] =
                        inputImageBits[ newY * oldWidthWithGarbage + newX ];
            }
        }
    } break;

    case QImage::Format::Format_RGB32:
    case QImage::Format::Format_ARGB32: {
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                int newX = int( double( x ) / _scaleWidth );
                int newY = int( double( y ) / _scaleHeight );

                int offsetInput = newY * width * 4 + newX * 4;
                int offsetOutput = y * newWidth * 4 + x * 4;

                outputImageBits[ offsetOutput++ ] = inputImageBits[ offsetInput++ ];
                outputImageBits[ offsetOutput++ ] = inputImageBits[ offsetInput++ ];
                outputImageBits[ offsetOutput++ ] = inputImageBits[ offsetInput++ ];
                outputImageBits[ offsetOutput ] = inputImageBits[ offsetInput ];
            }
        }
    } break;

    default: return image;
    }

    return newImage;
}

std::pair<double, double> ScaleProcessor::scale() const noexcept
{
    return { _scaleWidth, _scaleHeight };
}

void ScaleProcessor::setScale(double scaleWidth, double scaleHeight) noexcept(false)
{
    if ( scaleWidth < 0.01 || scaleHeight < 0.01 ) {
        throw std::out_of_range("[SetScale]#: Minimum scale factor 0.01!");
    }
    _scaleWidth = scaleWidth;
    _scaleHeight = scaleHeight;
}

double ScaleProcessor::scaleWidth() const noexcept
{
    return _scaleWidth;
}

void ScaleProcessor::setScaleWidth(double scale) noexcept(false)
{
    if ( scale < 0.01 ) {
        throw std::out_of_range("[SetScaleWidth]#: Minimum scale factor 0.01!");
    }
    _scaleWidth = scale;
}

double ScaleProcessor::scaleHeight() const noexcept
{
    return _scaleHeight;
}

void ScaleProcessor::setScaleHeight(double scale) noexcept(false)
{
    if ( scale < 0.01 ) {
        throw std::out_of_range("[SetScaleHeight]#: Minimum scale factor 0.01!");
    }
    _scaleHeight = scale;
}
