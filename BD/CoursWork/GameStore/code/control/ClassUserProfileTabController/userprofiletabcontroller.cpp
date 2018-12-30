#include "userprofiletabcontroller.h"
#include "ui_mainwindow.h"
#include "code/control/ClassAccountController/accountcontroller.h"
#include "code/control/ClassLoginWidget/loginwidget.h"
#include "code/control/CLassRegistrationWidget/registrationwidget.h"

#include <QMessageBox>

UserProfileTabController::UserProfileTabController(Ui::MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
    onUserLogout();

    loginDialog = new LoginWidget(mainWindow->centralWidget->parentWidget(), mainWindow->centralWidget);
    registrationDialog = new RegistrationWidget(mainWindow->centralWidget->parentWidget(), mainWindow->centralWidget);

    connect(&AccountController::get(), &AccountController::userLoggedIn,
            this, &UserProfileTabController::onUserLogin);
    connect(&AccountController::get(), &AccountController::userLoggedOut,
            this, &UserProfileTabController::onUserLogout);
    connect(&AccountController::get(), &AccountController::updateUserInfo,
            this, &UserProfileTabController::onUpdateUserInfo);
    connect(mainWindow->buttonLogin, &QPushButton::clicked,
            loginDialog, &LoginWidget::showDialog);
    connect(mainWindow->buttonRegistration, &QPushButton::clicked,
            registrationDialog, &RegistrationWidget::showDialog);
    connect(mainWindow->buttonLogout, &QPushButton::clicked, this, [mainWindow](){
        try {
            AccountController::get().logout();
        }
        catch ( QString& errorMsg ) {
            QMessageBox errorMsgDialog(mainWindow->centralWidget->parentWidget());
            errorMsgDialog.setModal(true);
            errorMsgDialog.setWindowTitle("Ошибка!");
            errorMsgDialog.setText(errorMsg);
            errorMsgDialog.setIcon(QMessageBox::Icon::Critical);
            errorMsgDialog.exec();
        }
    });
}

UserProfileTabController::~UserProfileTabController()
{
    delete loginDialog;
    delete registrationDialog;
}

void UserProfileTabController::onUserLogin()
{
    mainWindow->buttonLogin->hide();
    mainWindow->buttonRegistration->hide();

    mainWindow->buttonLogout->show();
    mainWindow->labelUserNickname->show();
    mainWindow->labelUserMoney->show();

    auto user = AccountController::get().user();
    mainWindow->labelUserNickname->setText(user.nickname);
    mainWindow->labelUserMoney->setText(QString("$%1").arg(user.money));
}

void UserProfileTabController::onUserLogout()
{
    mainWindow->buttonLogin->show();
    mainWindow->buttonRegistration->show();

    mainWindow->buttonLogout->hide();
    mainWindow->labelUserNickname->hide();
    mainWindow->labelUserMoney->hide();
}

void UserProfileTabController::onUpdateUserInfo()
{
    auto user = AccountController::get().user();
    mainWindow->labelUserNickname->setText(user.nickname);
    mainWindow->labelUserMoney->setText(QString("$%1").arg(user.money));
    mainWindow->mainTabWidget->setTabText(mainWindow->mainTabWidget->indexOf(mainWindow->tabUser), user.nickname);
}
