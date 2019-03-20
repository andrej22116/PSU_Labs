#include "EmbossProcessor.hpp"

#include <QImage>


EmbossProcessor::EmbossProcessor(int angle) noexcept
{
    _matrix = matrix(angle);
}

QImage EmbossProcessor::operator () (const QImage& image) noexcept
{
    double scaleWidth = static_cast<double>(image.width() + 3)
                      / static_cast<double>(image.width());
    double scaleHeight = static_cast<double>(image.height() + 3)
                       / static_cast<double>(image.height());

    QImage scaledSource = ScaleProcessor{ scaleWidth, scaleHeight }(image);
    {
        QPainter painter { &scaledSource };
        painter.drawImage(QPoint{1, 1}, image);
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

std::vector<double> EmbossProcessor::matrix(int angle)
{
    std::vector<double> matrix {
         -1, -1, -1, 0, 1, 1, 1, 0, 0
    };

    int rotate = static_cast<int>(static_cast<double>(angle) / 45.0);
    if (rotate > 0) {
        std::rotate(matrix.begin(), matrix.end() - rotate - 1, matrix.end() - 1);
    }

    std::vector<double> newMatrix{ matrix };

    int ost = angle % 45;

    double weightLeft = static_cast<double>(ost) / 45.0;

    double weightRight = 1.0 - weightLeft;

    if ( ost > 0 ) {
        for (int i = 0; i < 8; ++i) {
            double delta = static_cast<double>(matrix[i]) - static_cast<double>(matrix[(i + 1) % 8]);
            newMatrix[i] += delta * weightLeft;
            newMatrix[(i + 1) % 8] -= delta * weightRight;
        }
    }

    return {
        newMatrix[0], newMatrix[1], newMatrix[2],
        newMatrix[7], newMatrix[8], newMatrix[3],
        newMatrix[6], newMatrix[5], newMatrix[4]
    };
}

void EmbossProcessor::rgbProcessing(const QImage& inputImage, QImage& outputImage)
{
    auto inputBits = inputImage.bits();
    auto outputBits = outputImage.bits();

    auto width = outputImage.width();
    auto height = outputImage.height();

    auto bytesPerLine = inputImage.bytesPerLine();

    std::vector<const uchar*> maskOffsets;
    maskOffsets.reserve(8);

    for ( int y = 0; y < height; ++y ) {
        maskOffsets.clear();

        for ( int coreY = 0; coreY < 3; ++coreY ) {
            for ( int coreX = 0; coreX < 3; ++coreX ) {
                maskOffsets.push_back(inputBits + (bytesPerLine * (coreY + y)) + (coreX * 4));
            }
        }

        for ( int x = 0; x < width; ++x ) {
            double redComponent   = 0;
            double greenComponent = 0;
            double blueComponent  = 0;
            double alphaComponent = 0;

            for ( size_t i = 0, size = _matrix.size(); i < size; ++i ) {
                redComponent    += static_cast<double>((*maskOffsets[i]++) * _matrix[i]);
                greenComponent  += static_cast<double>((*maskOffsets[i]++) * _matrix[i]);
                blueComponent   += static_cast<double>((*maskOffsets[i]++) * _matrix[i]);
                alphaComponent  += static_cast<double>((*maskOffsets[i]++) * _matrix[i]);
            }

            redComponent   += 128;
            greenComponent += 128;
            blueComponent  += 128;
            alphaComponent += 128;

            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(redComponent)));
            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(greenComponent)));
            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(blueComponent)));
            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(alphaComponent)));
        }
    }
}

void EmbossProcessor::grayProcessing(const QImage& inputImage, QImage& outputImage)
{
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
            int grayComponent = 0;

            for ( size_t i = 0, size = _matrix.size(); i < size; ++i ) {
                grayComponent    += static_cast<int>((*maskOffsets[i]++) * _matrix[i]);
            }

            grayComponent += 128;
            *outputBits++ = static_cast<uchar>(MacCloseOnRange(0, 255, static_cast<int>(grayComponent)));
        }

        outputBits += shit;
    }
}
