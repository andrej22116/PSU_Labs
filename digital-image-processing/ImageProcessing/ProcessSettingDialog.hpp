#ifndef PROCESSSETTINGDIALOG_H
#define PROCESSSETTINGDIALOG_H

#include <QDialog>
#include <memory>
#include <ImageController.hpp>

namespace Ui {
class ProcessSettingDialog;
}

class QImage;
class WaitAnimationOverlayWidget;

class ProcessSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessSettingDialog(QWidget *parent = nullptr);
    ~ProcessSettingDialog() override;

    void setImage(const QImage& image);
    void setImage(QImage&& image);
    virtual ImageProcessor imageProcessor() = 0;

protected:
    void updatePreviewImage();

private:
    void setImage();

private slots:
    void onEndProcess();

protected:
    QWidget* centralWidget;
    ImageController _imageController;

private:
    inline static int IMAGE_SHORT_SIDE_LENGTH = 300;

    Ui::ProcessSettingDialog *ui;
    WaitAnimationOverlayWidget* _waitAnimationOverlayWidget;

};

#endif // PROCESSSETTINGDIALOG_H
