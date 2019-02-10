#include "ImageController.hpp"

#include <QImage>

ImageController::ImageController() :
    _initialImage( new QImage{} ),
    _finalImage( new QImage{} )
{

}

ImageController::ImageController(const QImage& image) :
    _initialImage( new QImage{ image } ),
    _finalImage( new QImage{} )
{
}

void ImageController::load(const QString& path)
{
    _initialImage = std::make_shared<QImage>(path);

    if ( _initialImage->isNull() ) {
        throw LoadImageException{};
    }

    emit loadEnded();
}

void ImageController::save(const QString& path)
{
    if (    !_initialImage
         ||  _initialImage->isNull()
         || !_initialImage->save(path)  ) {
        throw SaveImageException{};
    }

    _initialImage->save(path);
    emit saveEnded();
}

void ImageController::process(const ImageProcessor& processor)
{
    if ( !_initialImage ) {
        throw ProcessException{};
    }

    _finalImage = std::make_shared<QImage>(processor(*_initialImage));

    emit processEnded();
}

void ImageController::apply() noexcept
{
    if ( !_finalImage || _finalImage->isNull() ) {
        return;
    }

    std::swap(_initialImage, _finalImage);
    _finalImage.reset();

    emit applied();
}

void ImageController::setImage(const QImage& image)
{
    _initialImage = std::make_shared<QImage>(image);
}

void ImageController::setImage(QImage&& image)
{
    _initialImage = std::make_shared<QImage>(image);
}

const std::shared_ptr<QImage> ImageController::image() const
{
    return _initialImage;
}

const std::shared_ptr<QImage> ImageController::processedImage() const
{
    return _finalImage;
}

void LoadImageException::raise() const
{
    throw *this;
}

LoadImageException* LoadImageException::clone() const
{
    return new LoadImageException(*this);
}

void SaveImageException::raise() const
{
    throw *this;
}

SaveImageException* SaveImageException::clone() const
{
    return new SaveImageException(*this);
}

void ProcessException::raise() const
{
    throw *this;
}

ProcessException* ProcessException::clone() const
{
    return new ProcessException(*this);
}
