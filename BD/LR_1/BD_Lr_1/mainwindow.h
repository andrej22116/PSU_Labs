#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Math {
        Null, Add, Sub, Div, Mul, Pow
    };

    int task2_number;
    double task7_number;
    Math task7_math = Null;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void makeTask2();
    void makeTask3();
    void makeTask4();
    void makeTask5();
    void makeTask6();
    void makeTask7();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
