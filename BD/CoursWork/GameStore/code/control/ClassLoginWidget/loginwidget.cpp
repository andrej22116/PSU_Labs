#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "code/control/ClassAccountController/accountcontroller.h"

#include <QMessageBox>

LoginWidget::LoginWidget(QWidget *parent, QWidget* blurTarget) :
    BaseOverlayDialog(parent, blurTarget),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    connect(ui->buttonCancel, &QPushButton::clicked, this, &BaseOverlayDialog::hideDialog);
    connect(ui->editLogin, &QLineEdit::textChanged, this, &LoginWidget::testEditFields);
    connect(ui->editPassword, &QLineEdit::textChanged, this, &LoginWidget::testEditFields);
    connect(ui->buttonAuthorize, &QPushButton::clicked, this, &LoginWidget::onTryAuthorize);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::showDialog()
{
    ui->editLogin->setText("");
    ui->editPassword->setText("");
    BaseOverlayDialog::showDialog();
}

void LoginWidget::onTryAuthorize()
{
    try {
        AccountController::get().login(ui->editLogin->text(), ui->editPassword->text());
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

void LoginWidget::testEditFields()
{
    int loginTextLength = ui->editLogin->text().length();
    bool isValidLogin = loginTextLength >= 6 && loginTextLength <= 32;

    int passwordTextLength = ui->editPassword->text().length();
    bool isValidPassword = passwordTextLength >= 6 && passwordTextLength <= 32;

    if ( !isValidLogin || !isValidPassword ) {
        ui->buttonAuthorize->setDisabled(true);
    }
    else {
        ui->buttonAuthorize->setEnabled(true);
    }
}
