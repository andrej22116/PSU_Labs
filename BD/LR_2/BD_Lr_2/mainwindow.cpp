#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _loginOrRegisterDialog = new LoginOrRegisterDialog(this, ui->centralWidget);

    connect(ui->button_authorization, &QPushButton::clicked,
            _loginOrRegisterDialog, &LoginOrRegisterDialog::showLoginDialog);
    connect(ui->button_registration, &QPushButton::clicked,
            _loginOrRegisterDialog, &LoginOrRegisterDialog::showRegisterDialog);

    _loginOrRegisterDialog->showModal(ui->centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
