#include "GrayProcessor.hpp"

#include <QImage>


struct GrayProcessor::ProcessData {
    uchar oldOffset;
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
    QImage newImage(image.width(), image.height(), QImage::Format::Format_Grayscale8);

    uchar offset = 0;

    switch ( image.format() ) {
    case QImage::Format::Format_ARGB32:
    case QImage::Format::Format_RGB32: { offset = 4; } break;

    default: return image;
    }

    ProcessData data {
        offset,
        image.bits(),
        image.bits() + image.width() * image.height() * offset,
        newImage.bits(),
        newImage.bits() + newImage.width() * newImage.height()
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

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = *iteratorOld;
        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::greenProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = *(iteratorOld + 1);
        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::blueProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = *(iteratorOld + 2);
        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::deltaProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = ( *iteratorOld
                         + *(iteratorOld + 1)
                         + *(iteratorOld + 2)
                         ) / 3;

        iteratorOld += data.oldOffset;
    }
}

void GrayProcessor::smartProcess(ProcessData& data) noexcept
{
    auto iteratorOld = data.oldBegin;
    auto iteratorNew = data.newBegin;

    while ( iteratorOld != data.oldEnd ) {
        *iteratorNew++ = uchar( float( *iteratorOld )       * 0.2125f
                              + float( *(iteratorOld + 1) ) * 0.7154f
                              + float( *(iteratorOld + 2) ) * 0.0721f );

        iteratorOld += data.oldOffset;
    }
}
