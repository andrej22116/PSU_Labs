#ifndef GRAYPROCESSOR_H
#define GRAYPROCESSOR_H


class QImage;
using uchar = unsigned char;

class GrayProcessor
{
public:
    enum By {
        Red,
        Green,
        Blue,
        Delta,
        Smart
    };

    GrayProcessor(By by = Delta);

    QImage operator () (const QImage& image);

    By by() const noexcept;
    void setBy(By by) noexcept;

private:
    void redProcess(uchar* begin, uchar* end, uchar offset) noexcept;
    void greenProcess(uchar* begin, uchar* end, uchar offset) noexcept;
    void blueProcess(uchar* begin, uchar* end, uchar offset) noexcept;
    void deltaProcess(uchar* begin, uchar* end, uchar offset) noexcept;
    void smartProcess(uchar* begin, uchar* end, uchar offset) noexcept;

private:
    By _byComponent;

};

#endif // GRAYPROCESSOR_H
