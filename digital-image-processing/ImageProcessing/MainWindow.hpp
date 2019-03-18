#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ImageController;
class ProcessSettingDialog;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionGray_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionBin_triggered();

    void on_actionNoiseSaltAndPepper_triggered();

    void on_actionNoiseGause_triggered();

    void on_actionLightCorrection_triggered();

    void on_actionStamping_triggered();

    void on_actionFilterLL_triggered();

    void on_actionFilterHL_triggered();

    void on_actionFilterMedian_triggered();

    void on_actionBlure_triggered();

    void on_actionBorders_triggered();

private:
    void runProcessDialog(ProcessSettingDialog& dialog);
    void openImage();

private:
    Ui::MainWindow* ui;
    ImageController* _imageController;
    QString _savePath;

};

#endif // MAINWINDOW_H
