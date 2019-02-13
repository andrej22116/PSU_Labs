#include "BinaryProcessor.hpp"

#include <QImage>
#include "GrayProcessor.hpp"
#include <array>

BinaryProcessor::BinaryProcessor(BinaryProcessor::Method method) :
    _invert(false),
    _method(method)
{
}

QImage BinaryProcessor::operator ()(const QImage& image)
{
    switch ( _method ) {
    case Method::Base: {
        return doBaseMethod( GrayProcessor{ GrayProcessor::By::Smart }(image) );
    }

    case Method::Otsu: {
        return doOtsuMethod( GrayProcessor{ GrayProcessor::By::Smart }(image) );
    }

    case Method::BradleyAndRot: {
        return doBradleyAndRotMethod( GrayProcessor{ GrayProcessor::By::Smart }(image) );
    }
    }
}


QImage BinaryProcessor::doBaseMethod(const QImage& image)
{
    QImage newImage(image.width(), image.height(), QImage::Format_Grayscale8);

    doSimpleBinarization(image, newImage, 128);

    return newImage;
}

QImage BinaryProcessor::doOtsuMethod(const QImage& image)
{
    QImage newImage(image.width(), image.height(), QImage::Format_Grayscale8);

    doSimpleBinarization(image, newImage, otsuThreshold(image));

    return newImage;
}

QImage BinaryProcessor::doBradleyAndRotMethod(const QImage& image)
{
    return QImage();
}

void BinaryProcessor::doSimpleBinarization(const QImage& image, QImage& newImage, uchar threshold)
{
    int oldImageWidth = image.width();
    int oldImageHeight = image.height();
    int oldImageGarbage = int(image.sizeInBytes() / oldImageHeight) - oldImageWidth;

    auto oldImageIterator = image.bits();
    auto oldImageEnd = oldImageIterator + (oldImageWidth + oldImageGarbage) * oldImageHeight;
    auto newImageIterator = newImage.bits();

    uchar highIntencity = 255 * !_invert;
    uchar lowIntencity = 255 * _invert;

    while ( oldImageIterator != oldImageEnd ) {
        *newImageIterator = *oldImageIterator >= threshold ? highIntencity : lowIntencity;

        ++oldImageIterator;
        ++newImageIterator;
    }
}

uchar BinaryProcessor::otsuThreshold(const QImage& image)
{
    int imageWidth = image.width();
    int imageHeight = image.height();
    int imageBytes = imageWidth * imageHeight;
    int imageGarbage = int(image.sizeInBytes() / imageHeight) - imageWidth;

    auto imageBegin = image.bits();
    auto imageEnd = imageBegin + (imageWidth + imageGarbage) * imageHeight;

    std::array<uint, 256> histogram;
    long long int m = 0;

    memset(histogram.data(), 0, sizeof(uint) * 256);

    auto iterator = imageBegin;
    while ( iterator != imageEnd ) {
        for (auto lineEnd = iterator + imageWidth; iterator != lineEnd; ++iterator) {
            ++histogram[*iterator];
        }

        iterator += imageGarbage;
    }

    for (uint i = 0; i < 256; ++i) {
        m += i * histogram[i];
    }

    uchar bestThreshold = 0;
    double bestSigma = 0;

    int firstClassPixelCount = 0;
    int firstClassIntensitySum = 0;

    for (uchar threshold = 0; threshold < 255; ++threshold) {
        firstClassPixelCount += histogram[threshold];
        firstClassIntensitySum += threshold * histogram[threshold];

        double firstClassProb = firstClassPixelCount / static_cast<double>(imageBytes);
        double secondClassProb = 1.0 - firstClassProb;

        double firstClassMean = firstClassIntensitySum
                              / static_cast<double>(firstClassPixelCount);
        double secondClassMean = (m - firstClassIntensitySum)
                               / static_cast<double>(imageBytes - firstClassPixelCount);

        double meanDelta = firstClassMean - secondClassMean;

        double sigma = firstClassProb * secondClassProb * meanDelta * meanDelta;

        if (sigma > bestSigma) {
            bestSigma = sigma;
            bestThreshold = threshold;
        }
    }

    return bestThreshold;
}


bool BinaryProcessor::isInvert()
{
    return _invert;
}

void BinaryProcessor::setInvert(bool isInvert)
{
    _invert = isInvert;
}

BinaryProcessor::Method BinaryProcessor::method()
{
    return _method;
}

void BinaryProcessor::setMethod(BinaryProcessor::Method method)
{
    _method = method;
}
