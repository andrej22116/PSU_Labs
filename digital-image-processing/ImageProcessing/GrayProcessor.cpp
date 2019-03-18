#include "GrayProcessor.hpp"

#include <QImage>


struct GrayProcessor::ProcessData {
    uchar oldOffset;
    ushort width;
    const uchar* oldBegin;
    const uchar* oldEnd;
    uchar* newBegin;
    uchar* newEnd;
};



GrayProcessor::GrayProcessor(By by) :
    _byComponent(by)
{
}

QImage GrayProcessor::operator () (const QImage &image)
{
    uchar offset = 0;

    switch ( image.format() ) {
    case QImage::Format::Format_ARGB32:
    case QImage::Format::Format_RGB32: { offset = 4; } break;

    default: return image;
    }

    QImage newImage(image.width(), image.height(), QImage::Format::Format_Grayscale8);

    ProcessData data {
        offset,
        ushort(image.width()),
        image.bits(),
        image.bits() + image.width() * image.height() * offset,
        newImage.bits(),
        newImage.bits() + newImage.width() * newImage.height(),

    };

    switch ( _byComponent ) {
    case Red: { redProcess(data); } break;
    case Green: { greenProcess(data); } break;
    case Blue: { blueProcess(data); } break;
    case Delta: { deltaProcess(data); } break;
    case Smart: { smartProcess(data); } break;
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

void GrayProcessor::redProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    size_t lineOffset = 0;
    size_t lineGarbage = data.width % 4 ? 4 - data.width % 4 : 0;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = *iteratorOld;

        ++lineOffset;
        if ( lineOffset == data.width ) {
            iteratorNew += lineGarbage;
            lineOffset = 0;
        }

        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::greenProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    size_t lineOffset = 0;
    size_t lineGarbage = data.width % 4 ? 4 - data.width % 4 : 0;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = *(iteratorOld + 1);

        ++lineOffset;
        if ( lineOffset == data.width ) {
            iteratorNew += lineGarbage;
            lineOffset = 0;
        }

        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::blueProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    size_t lineOffset = 0;
    size_t lineGarbage = data.width % 4 ? 4 - data.width % 4 : 0;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = *(iteratorOld + 2);

        ++lineOffset;
        if ( lineOffset == data.width ) {
            iteratorNew += lineGarbage;
            lineOffset = 0;
        }

        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::deltaProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    size_t lineOffset = 0;
    size_t lineGarbage = data.width % 4 ? 4 - data.width % 4 : 0;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = ( *iteratorOld
                         + *(iteratorOld + 1)
                         + *(iteratorOld + 2)
                         ) / 3;

        ++lineOffset;
        if ( lineOffset == data.width ) {
            iteratorNew += lineGarbage;
            lineOffset = 0;
        }

        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::smartProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    size_t lineOffset = 0;
    size_t lineGarbage = data.width % 4 ? 4 - data.width % 4 : 0;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = uchar( float( *iteratorOld )       * 0.299f
                              + float( *(iteratorOld + 1) ) * 0.587f
                              + float( *(iteratorOld + 2) ) * 0.114f );

        ++lineOffset;
        if ( lineOffset == data.width ) {
            iteratorNew += lineGarbage;
            lineOffset = 0;
        }

        iteratorOld += data.oldOffset;
    }
}
