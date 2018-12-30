#include "registrationwidget.h"
#include "ui_registrationwidget.h"

#include "code/control/ClassAccountController/accountcontroller.h"
#include <QMessageBox>

RegistrationWidget::RegistrationWidget(QWidget *parent, QWidget* blurTarget) :
    BaseOverlayDialog(parent, blurTarget),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);

    connect(ui->buttonCancel, &QPushButton::clicked, this, &RegistrationWidget::hideDialog);
    connect(ui->editNickname, &QLineEdit::textChanged, this, &RegistrationWidget::testEditFields);
    connect(ui->editLogin, &QLineEdit::textChanged, this, &RegistrationWidget::testEditFields);
    connect(ui->editPassword, &QLineEdit::textChanged, this, &RegistrationWidget::testEditFields);
    connect(ui->editRepeatPassword, &QLineEdit::textChanged, this, &RegistrationWidget::testEditFields);
    connect(ui->buttonRegistration, &QPushButton::clicked, this, &RegistrationWidget::onTryRegistration);
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}

void RegistrationWidget::showDialog()
{
    ui->editNickname->setText("");
    ui->editLogin->setText("");
    ui->editPassword->setText("");
    ui->editRepeatPassword->setText("");
    BaseOverlayDialog::showDialog();
}

void RegistrationWidget::onTryRegistration()
{
    try {
        AccountController::get().registration( ui->editLogin->text()
                                             , ui->editPassword->text()
                                             , ui->editNickname->text());
        hideDialog();
    }
    catch ( QString& errorMsg ) {
        QMessageBox errorMsgDialog(this);
        errorMsgDialog.setModal(true);
        errorMsgDialog.setWindowTitle("Ошибка!");
        errorMsgDialog.setText(errorMsg);
        errorMsgDialog.setIcon(QMessageBox::Icon::Critical);
        errorMsgDialog.exec();
    }
}

void RegistrationWidget::testEditFields()
{
    int nicknameTextLength = ui->editNickname->text().length();
    bool isValidNickname = nicknameTextLength >= 6 && nicknameTextLength <= 32;

    int loginTextLength = ui->editLogin->text().length();
    bool isValidLogin = loginTextLength >= 6 && loginTextLength <= 32;

    int passwordTextLength = ui->editPassword->text().length();
    bool isValidPassword = passwordTextLength >= 6 && passwordTextLength <= 32;

    bool passwordsMatch = ui->editPassword->text() == ui->editRepeatPassword->text();

    if ( !nicknameTextLength || !isValidLogin || !isValidPassword || !passwordsMatch ) {
        ui->buttonRegistration->setDisabled(true);
    }
    else {
        ui->buttonRegistration->setEnabled(true);
    }
}
