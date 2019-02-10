#include "ScaleProcessor.hpp"
#include <stdexcept>

#include <QImage>

ScaleProcessor::ScaleProcessor()
{

}

QImage ScaleProcessor::operator ()(const QImage& image) noexcept(false)
{
    int width = image.width();
    int height = image.height();
    int newWindth = int( width * _scaleWidth );
    int newheight = int( height * _scaleHeight );

    QImage newImage{ newWindth, newheight, image.format() };

    auto inputImageBits = image.bits();
    auto outputImageBits = newImage.bits();

    int inputBitsCount = image.width() * image.height() * 4;

    auto iterator = inputImageBits;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

        }
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
