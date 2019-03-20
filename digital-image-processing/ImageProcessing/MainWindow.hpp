#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ImageController;
class ProcessSettingDialog;
class QLabel;
class WaitAnimationOverlayWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

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

    void on_actionScale_triggered();

private:
    void runProcessDialog(ProcessSettingDialog& dialog);
    void openImage();

    void updateStatusBar();

    void disableAllActions();
    void enableAllActions();
    void disableAllAlgorithmActions();
    void enableAllAlgorithmActions();

private slots:
    void onEndProcess();

    void on_actionExit_triggered();

    void on_actionContrast_triggered();

private:
    Ui::MainWindow* ui;
    ImageController* _imageController;
    QLabel* _labelPath;
    QLabel* _labelSize;
    QString _savePath;
    WaitAnimationOverlayWidget* _waitAnimationOverlayWidget;

};

#endif // MAINWINDOW_H
