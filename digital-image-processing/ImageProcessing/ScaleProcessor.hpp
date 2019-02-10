#ifndef SCALEPROCESSOR_H
#define SCALEPROCESSOR_H

#include <utility>

class QImage;


class ScaleProcessor
{    
public:
    enum Method {
        NearestNeighbor,    // Метод ближайшего соседа
        Bilinear,           // Афинный билинейный метод
        Bisquare,           // Афинный бикубический метод
        Supersampling,      // Суперсэмплинг
        Convolution         // Свёртка
    };


    ScaleProcessor(Method method = NearestNeighbor);

    QImage operator () (const QImage& image);

    std::pair<double, double> scale() const noexcept;
    void setScale(double scaleWidth, double scaleHeight) noexcept(false);

    double scaleWidth() const noexcept;
    void setScaleWidth(double scale) noexcept(false);

    double scaleHeight() const noexcept;
    void setScaleHeight(double scale) noexcept(false);

private:

private:
    double _scaleWidth;
    double _scaleHeight;
};


#endif // SCALEPROCESSOR_H
