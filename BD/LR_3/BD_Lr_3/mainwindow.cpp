#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include "src/ClassDateValidator/datevalidator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nameValidator = new QRegExpValidator(QRegExp("^(\\D)+$"));
    dateValidator = new DateValidator('.');

    ui->lineEditFio->setValidator(nameValidator);
    ui->lineEditBornDate->setValidator(dateValidator);

    ui->checkBoxConfirmation->setCheckState(Qt::CheckState::Checked);
    ui->radioButtonTxt->setChecked(true);

    connect(ui->buttonAdd, &QPushButton::clicked, this, &MainWindow::onClick_buttonAdd);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onClick_buttonAdd(bool checked)
{
    if ( !ui->lineEditFio->hasAcceptableInput() ) { return; }
    if ( !ui->lineEditBornDate->hasAcceptableInput() ) { return; }
    if ( !ui->lineEditNumber->hasAcceptableInput() ) { return; }
    if ( ui->lineEditGroup->text().length() == 0 ) { return; }
    if ( ui->lineEditAddres->text().length() == 0 ) { return; }

    ui->statusBar->showMessage("Запись успешно добавлена!", 5000);
}
