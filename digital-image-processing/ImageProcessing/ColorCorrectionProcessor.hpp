#ifndef COLORCORRECTIONPROCESSOR_HPP
#define COLORCORRECTIONPROCESSOR_HPP


class QImage;

class ColorCorrectionProcessor
{
public:
    ColorCorrectionProcessor(float power = 0.0f);

    QImage operator () (const QImage& image) noexcept;

    float power() noexcept;
    void setPower(float power) noexcept(false);

private:
    void rgbCorrection(const QImage& inputImage, QImage& outputImage) noexcept;
    void grayCorrection(const QImage& inputImage, QImage& outputImage) noexcept;

private:
    float _power;
};

#endif // COLORCORRECTIONPROCESSOR_HPP
