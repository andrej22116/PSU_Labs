#ifndef CONTRASTPROCESSOR_HPP
#define CONTRASTPROCESSOR_HPP

#include <vector>


class QImage;


class ContrastProcessor
{
public:
    enum class ContrastAlgorithm {
        Laplas,
        Previtt,
        Roberts,
        Sobel
    };

    ContrastProcessor(ContrastAlgorithm algorithm = ContrastAlgorithm::Laplas);

    QImage operator () (const QImage& image) noexcept;

    ContrastAlgorithm contrastAlgorithm() { return _algorithm; }
    void setContrastAlgorithm(ContrastAlgorithm algorithm) { _algorithm = algorithm; }

private:
    void laplasProcess(const QImage& inputImage, QImage& outputImage);
    void previttAndSobelProcess(const QImage& inputImage, QImage& outputImage);
    void robertsProcess(const QImage& inputImage, QImage& outputImage);

    std::vector<double> getLaplasMatrix();
    std::pair<std::vector<int>, std::vector<int>> getPrevitMatrix();
    std::pair<std::vector<int>, std::vector<int>> getRobertsMatrix();
    std::pair<std::vector<int>, std::vector<int>> getSobelMatrix();

private:
    int _angle;
    ContrastAlgorithm _algorithm;
};

#endif // CONTRASTPROCESSOR_HPP
