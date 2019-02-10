#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <QException>
#include <memory>
#include <functional>


class QImage;

using uchar = unsigned char;
using ImageProcessor = std::function<QImage (const QImage&)>;

class ImageController : public QObject
{
    Q_OBJECT

public:
    ImageController();
    ImageController(const QImage& image);

    void load(const QString& path) noexcept(false);
    void save(const QString& path) noexcept(false);

    void process(const ImageProcessor& processor) noexcept(false);
    void apply() noexcept;

    void setImage(const QImage& image);
    void setImage(QImage&& image);
    const std::shared_ptr<QImage> image() const;
    const std::shared_ptr<QImage> processedImage() const;

signals:
    void processEnded();
    void applied();
    void loadEnded();
    void saveEnded();

private:
    std::shared_ptr<QImage> _initialImage;
    std::shared_ptr<QImage> _finalImage;
};


class LoadImageException : public QException {
    void raise() const override;
    LoadImageException* clone() const override;
};

class SaveImageException : public QException {
    void raise() const override;
    SaveImageException* clone() const override;
};

class ProcessException : public QException {
    void raise() const override;
    ProcessException* clone() const override;
};

#endif // IMAGECONTROLLER_H
