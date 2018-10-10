#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ClassLoginOrRegisterDialog/loginorregisterdialog.h"

namespace Ui {
class MainWindow;
}

//class LoginOrRegisterDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    LoginOrRegisterDialog* _loginOrRegisterDialog;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
