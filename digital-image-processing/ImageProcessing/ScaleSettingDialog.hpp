#ifndef SCALESETTINGDIALOG_HPP
#define SCALESETTINGDIALOG_HPP

#include <QDialog>
#include <functional>

namespace Ui {
class ScaleSettingDialog;
}

class QImage;
using ImageProcessor = std::function<QImage (const QImage&)>;

class ScaleSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleSettingDialog(int oldWidth, int oldHeight, QWidget *parent = nullptr);
    ~ScaleSettingDialog();

    ImageProcessor imageProcessor();

private:
    Ui::ScaleSettingDialog *ui;
    int _oldWidth;
    int _oldHeight;
};

#endif // SCALESETTINGDIALOG_HPP
