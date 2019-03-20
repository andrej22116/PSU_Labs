#ifndef EMBOSSPROCESSOR_HPP
#define EMBOSSPROCESSOR_HPP


#include "BaseMatrixCoreProcessor.hpp"
#include <vector>

class EmbossProcessor
{
    std::vector<double> _matrix;

public:
    EmbossProcessor(int angle) noexcept;

    QImage operator () (const QImage& image) noexcept;

    static std::vector<double> matrix(int angle);

protected:
    void rgbProcessing(const QImage& inputImage, QImage& outputImage);
    void grayProcessing(const QImage& inputImage, QImage& outputImage);
};

#endif // EMBOSSPROCESSOR_HPP
