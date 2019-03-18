#ifndef SALTANDPAPEERNOISEPROCESSOR_HPP
#define SALTANDPAPEERNOISEPROCESSOR_HPP

#include <random>

class QImage;

using ushort = unsigned short;

class SaltAndPapeerNoiseProcessor
{
public:
    SaltAndPapeerNoiseProcessor(ushort tresholdChance = 100);

    QImage operator () (const QImage& image) noexcept;

    ushort tresholChance() noexcept;
    void setTresholdChance(ushort tresholdChance) noexcept(false);

public:
    inline static ushort MAX_TRESHHOLD_CHANCE = 10000;
    inline static ushort MIN_TRESHHOLD_CHANCE = 100;

private:
    void colorNoise(const QImage& inputImage, QImage& outputImage) noexcept;
    void grayNoise(const QImage& inputImage, QImage& outputImage) noexcept;

private:
    ushort _tresholdChance;

    std::mt19937 _generator{ std::random_device{}() };
    std::uniform_int_distribution<ushort> _distribution {
        MIN_TRESHHOLD_CHANCE,
        MAX_TRESHHOLD_CHANCE
    };
};

#endif // SALTANDPAPEERNOISEPROCESSOR_HPP
