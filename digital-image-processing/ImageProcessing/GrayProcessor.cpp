#include "GrayProcessor.hpp"

#include <QImage>

GrayProcessor::GrayProcessor(By by) :
    _byComponent(by)
{
}

QImage GrayProcessor::operator () (const QImage &image)
{
    auto newImage = image.copy();
    uchar* bits = newImage.bits();
    uchar offset = 0;

    switch ( image.format() ) {
    case QImage::Format::Format_ARGB32: { offset = 1; } break;
    case QImage::Format::Format_RGB32: { offset = 1; } break;
    default: return image;
    }

    int bitsCount = image.width() * image.height() * ( 3 + offset );

    uchar* beginPointer = bits;
    uchar* endPointer = bits + bitsCount;

    switch ( _byComponent ) {
    case Red: { redProcess(beginPointer, endPointer, offset); } break;
    case Green: { greenProcess(beginPointer, endPointer, offset); } break;
    case Blue: { blueProcess(beginPointer, endPointer, offset); } break;
    case Delta: { deltaProcess(beginPointer, endPointer, offset); } break;
    case Smart: { smartProcess(beginPointer, endPointer, offset); } break;
    }

    return newImage;
}

GrayProcessor::By GrayProcessor::by() const noexcept
{
    return _byComponent;
}

void GrayProcessor::setBy(GrayProcessor::By by) noexcept
{
    _byComponent = by;
}

void GrayProcessor::redProcess(uchar* begin, uchar* end, uchar offset) noexcept
{
    while ( begin != end ) {
        uchar newValue = *begin;

        *begin++ = newValue;
        *begin++ = newValue;
        *begin++ = newValue;

        begin += offset;
    }
}

void GrayProcessor::greenProcess(uchar* begin, uchar* end, uchar offset) noexcept
{
    while ( begin != end ) {
        uchar newValue = *(begin + 1);

        *begin++ = newValue;
        *begin++ = newValue;
        *begin++ = newValue;

        begin += offset;
    }
}

void GrayProcessor::blueProcess(uchar* begin, uchar* end, uchar offset) noexcept
{
    while ( begin != end ) {
        uchar newValue = *(begin + 2);

        *begin++ = newValue;
        *begin++ = newValue;
        *begin++ = newValue;

        begin += offset;
    }
}

void GrayProcessor::deltaProcess(uchar* begin, uchar* end, uchar offset) noexcept
{
    while ( begin != end ) {
        uchar newValue = (*begin + *(begin + 1) + *(begin + 2)) / 3;

        *begin++ = newValue;
        *begin++ = newValue;
        *begin++ = newValue;

        begin += offset;
    }
}

void GrayProcessor::smartProcess(uchar* begin, uchar* end, uchar offset) noexcept
{
    while ( begin != end ) {
        uchar newValue = uchar( float( *begin )       * 0.3f
                              + float( *(begin + 1) ) * 0.59f
                              + float( *(begin + 2) ) * 0.11f );

        *begin++ = newValue;
        *begin++ = newValue;
        *begin++ = newValue;

        begin += offset;
    }
}
