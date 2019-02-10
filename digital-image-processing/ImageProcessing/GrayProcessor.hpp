#ifndef GRAYPROCESSOR_H
#define GRAYPROCESSOR_H


class QImage;

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
    struct ProcessData;

    void redProcess(ProcessData& data) noexcept;
    void greenProcess(ProcessData& data) noexcept;
    void blueProcess(ProcessData& data) noexcept;
    void deltaProcess(ProcessData& data) noexcept;
    void smartProcess(ProcessData& data) noexcept;

private:
    By _byComponent;

};

#endif // GRAYPROCESSOR_H
