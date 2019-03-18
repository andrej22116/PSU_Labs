#ifndef MEDIANFILTERPROCESSOR_HPP
#define MEDIANFILTERPROCESSOR_HPP


class QImage;


class MedianFilterProcessor
{
public:
    enum class Mask {
        Mask_3x3,
        Mask_5x5,
        Mask_7x7
    };

    MedianFilterProcessor(Mask mask = Mask::Mask_3x3);

    QImage operator () (const QImage& image);

private:
    void rgbProcessing(const QImage& inputImage, QImage& outputImage);
    void grayProcessing(const QImage& inputImage, QImage& outputImage);

private:
    Mask _mask;
    char _coreSize;
    char _coreHalfSize;
};

#endif // MEDIANFILTERPROCESSOR_HPP
