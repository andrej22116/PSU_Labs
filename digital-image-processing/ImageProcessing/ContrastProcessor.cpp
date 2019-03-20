#include "ContrastProcessor.hpp"
#include <QImage>
#include <cmath>

#include "GrayProcessor.hpp"
#include "ScaleProcessor.hpp"
#include <QPainter>


#define MacCloseOnRange(min, max, value)    \
        ( (value) > (max) ? (max) :         \
          (value) < (min) ? (min) :         \
          (value)                           \
        )



ContrastProcessor::ContrastProcessor(ContrastAlgorithm algorithm) :
    _algorithm(algorithm)
{

}

QImage ContrastProcessor::operator () (const QImage& image) noexcept
{
    QImage grayImage = GrayProcessor{GrayProcessor::By::Smart}(image);

    switch ( _algorithm ) {
    case ContrastAlgorithm::Laplas: {
        QImage out{grayImage.size(), grayImage.format()};
        laplasProcess(image, out);
        return out;
        break;
    }
    case ContrastAlgorithm::Sobel:
    case ContrastAlgorithm::Previtt:
    case ContrastAlgorithm::Roberts: {
        double scaleWidth = static_cast<double>(image.width() + 3)
                          / static_cast<double>(image.width());
        double scaleHeight = static_cast<double>(image.height() + 3)
                           / static_cast<double>(image.height());

        QImage scaledSource = ScaleProcessor{ scaleWidth, scaleHeight }(grayImage);
        {
            QPainter painter { &scaledSource };
            painter.drawImage(QPoint{1, 1}, grayImage);
            painter.end();
        }

        QImage result { grayImage.size(), grayImage.format() };

        switch ( _algorithm ) {
        case ContrastAlgorithm::Sobel: { previttAndSobelProcess(scaledSource, result); break; }
        case ContrastAlgorithm::Previtt: { previttAndSobelProcess(scaledSource, result); break; }
        case ContrastAlgorithm::Roberts: { robertsProcess(scaledSource, result); break; }
        default: break;
        }

        return result;
    }
    }
}

void ContrastProcessor::laplasProcess(const QImage &inputImage, QImage &outputImage)
{

}

void ContrastProcessor::previttAndSobelProcess(const QImage &inputImage, QImage &outputImage)
{
    auto matrix = _algorithm == ContrastAlgorithm::Previtt ? getPrevitMatrix() : getRobertsMatrix();

    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto width = outputImage.width();
    auto height = outputImage.height();

    auto bytesPerLine = inputImage.bytesPerLine();
    auto shit = outputImage.bytesPerLine() - width;

    std::vector<const uchar*> maskOffsets;
    maskOffsets.reserve(8);

    for ( int y = 0; y < height; ++y ) {
        maskOffsets.clear();

        for ( int coreY = 0; coreY < 3; ++coreY ) {
            for ( int coreX = 0; coreX < 3; ++coreX ) {
                maskOffsets.push_back(inputBits + (bytesPerLine * (coreY + y)) + coreX);
            }
        }

        for ( int x = 0; x < width; ++x ) {
            int grayComponent_1 = 0;
            int grayComponent_2 = 0;

            for ( int i = 0, size = matrix.first.size(); i < size; ++i ) {
                grayComponent_1    += (*maskOffsets[i]) * matrix.first[i];
                grayComponent_2    += (*maskOffsets[i]) * matrix.second[i];
                ++maskOffsets[i];
            }

            int res = static_cast<int>(sqrt(grayComponent_1 * grayComponent_1 + grayComponent_2 * grayComponent_2));
            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, res));
        }

        outputBits += shit;
    }
}

void ContrastProcessor::robertsProcess(const QImage &inputImage, QImage &outputImage)
{
    auto matrix = _algorithm == ContrastAlgorithm::Previtt ? getPrevitMatrix() : getRobertsMatrix();

    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto width = outputImage.width();
    auto height = outputImage.height();

    auto bytesPerLine = inputImage.bytesPerLine();
    auto shit = outputImage.bytesPerLine() - width;

    std::vector<const uchar*> maskOffsets;
    maskOffsets.reserve(8);

    for ( int y = 0; y < height; ++y ) {
        maskOffsets.clear();

        for ( int coreY = 0; coreY < 2; ++coreY ) {
            for ( int coreX = 0; coreX < 2; ++coreX ) {
                maskOffsets.push_back(inputBits + (bytesPerLine * (coreY + y)) + coreX + 1);
            }
        }

        for ( int x = 0; x < width; ++x ) {
            int grayComponent_1 = 0;
            int grayComponent_2 = 0;

            for ( int i = 0, size = matrix.first.size(); i < size; ++i ) {
                grayComponent_1    += (*maskOffsets[i]) * matrix.first[i];
                grayComponent_2    += (*maskOffsets[i]) * matrix.second[i];
                ++maskOffsets[i];
            }

            int res = static_cast<int>(sqrt(grayComponent_1 * grayComponent_1 + grayComponent_2 * grayComponent_2));
            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, res));
        }

        outputBits += shit;
    }
}

std::pair<std::vector<int>, std::vector<int> > ContrastProcessor::getPrevitMatrix()
{
    return {
        {-1, -1, -1, 0, 0, 0, 1, 1, 1},
        {-1, 0, 1, -1, 0, 1, -1, 0, 1}
    };
}

std::pair<std::vector<int>, std::vector<int> > ContrastProcessor::getSobelMatrix()
{
    return {
        {-1, -2, -1, 0, 0, 0, 1, 2, 1},
        {-1, 0, 1, -2, 0, 2, -1, 0, 1}
    };
}

std::pair<std::vector<int>, std::vector<int> > ContrastProcessor::getRobertsMatrix()
{
    return {
        {-1, 0, 0, 1},
        {0, -1, 1, 0}
    };
}
