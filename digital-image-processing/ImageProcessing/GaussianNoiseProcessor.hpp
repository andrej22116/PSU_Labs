#ifndef GAUSSIANNOISEPROCESSOR_HPP
#define GAUSSIANNOISEPROCESSOR_HPP


#include <random>


class QImage;

class GaussianNoiseProcessor
{
public:
    GaussianNoiseProcessor();

    QImage operator () (const QImage& image) noexcept;

private:
    void colorNoise(const QImage& inputImage, QImage& outputImage) noexcept;
    void grayNoise(const QImage& inputImage, QImage& outputImage) noexcept;

private:
    std::mt19937 _generator{ std::random_device{}() };
    std::normal_distribution<double> _distribution { 0.0, 0.1 };
};

#endif // GAUSSIANNOISEPROCESSOR_HPP
