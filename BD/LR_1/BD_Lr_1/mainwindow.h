#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int task2_number;

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
