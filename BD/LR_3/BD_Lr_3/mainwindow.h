#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QValidator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QValidator* nameValidator = nullptr;
    QValidator* dateValidator = nullptr;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onClick_buttonAdd(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
