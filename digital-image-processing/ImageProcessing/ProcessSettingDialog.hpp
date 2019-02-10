#ifndef PROCESSSETTINGDIALOG_H
#define PROCESSSETTINGDIALOG_H

#include <QDialog>
#include <memory>
#include <ImageController.hpp>

namespace Ui {
class ProcessSettingDialog;
}

class QImage;

class ProcessSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessSettingDialog(QWidget *parent = nullptr);
    ~ProcessSettingDialog();

    void setImage(const QImage& image);
    virtual ImageProcessor imageProcessor() = 0;

private:
    Ui::ProcessSettingDialog *ui;
    ImageController _imageController;
};

#endif // PROCESSSETTINGDIALOG_H
