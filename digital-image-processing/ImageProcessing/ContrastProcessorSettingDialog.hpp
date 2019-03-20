#ifndef CONTRASTPROCESSORSETTINGDIALOG_HPP
#define CONTRASTPROCESSORSETTINGDIALOG_HPP

#include "ProcessSettingDialog.hpp"

namespace Ui {
class ContrastProcessorSettingDialog;
}

class ContrastProcessorSettingDialog : public ProcessSettingDialog
{
    Q_OBJECT

public:
    explicit ContrastProcessorSettingDialog(QWidget *parent = nullptr);
    ~ContrastProcessorSettingDialog();

    ImageProcessor imageProcessor() override;

private slots:
    void on_radioLaplas_toggled(bool checked);

    void on_radioPrevitt_toggled(bool checked);

    void on_radioRoberts_toggled(bool checked);

    void on_radioSobel_toggled(bool checked);

private:
    Ui::ContrastProcessorSettingDialog *ui;
    char _selectedAlgorithm;
};

#endif // CONTRASTPROCESSORSETTINGDIALOG_HPP
