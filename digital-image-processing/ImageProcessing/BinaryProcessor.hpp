#ifndef BINARYPROCESSOR_HPP
#define BINARYPROCESSOR_HPP


class QImage;

using uchar = unsigned char;

class BinaryProcessor
{
public:    
    enum Method {
        Base,
        Otsu,
        BradleyAndRot
    };

    BinaryProcessor(Method method = Base);

    QImage operator () (const QImage& image);

    bool isInvert();
    void setInvert(bool isInvert);

    Method method();
    void setMethod(Method method);

private:
    QImage doBaseMethod(const QImage& image);
    QImage doOtsuMethod(const QImage& image);
    QImage doBradleyAndRotMethod(const QImage& image);

    void doSimpleBinarization( const QImage& image
                             , QImage& newImage
                             , uchar threshold );

    uchar otsuThreshold(const QImage& image);

private:
    bool _invert;
    Method _method;
};

#endif // BINARYPROCESSOR_HPP
