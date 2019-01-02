#include "userprofiletabcontroller.h"
#include "ui_mainwindow.h"
#include "code/control/ClassAccountController/accountcontroller.h"
#include "code/control/ClassLoginWidget/loginwidget.h"
#include "code/control/CLassRegistrationWidget/registrationwidget.h"
#include "code/control/ClassMessenger/messenger.h"
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"

#include <QMessageBox>
#include <QDoubleValidator>

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
    connect(&AccountController::get(), &AccountController::userUpdatedInfo,
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
            Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
        }
    });


    connect(mainWindow->editUserProfileNewLogin, &QLineEdit::textChanged,
            this, &UserProfileTabController::onEnterTextForChangeLogin);
    connect(mainWindow->editUserProfileUserPassword, &QLineEdit::textChanged,
            this, &UserProfileTabController::onEnterTextForChangeLogin);
    connect(mainWindow->buttonChangeLogin, &QPushButton::clicked,
            this, &UserProfileTabController::onTryChangeLogin);

    connect(mainWindow->editUserProfileOldPassword, &QLineEdit::textChanged,
            this, &UserProfileTabController::onEnterTextForChangePassword);
    connect(mainWindow->editUserProfileNewPassword, &QLineEdit::textChanged,
            this, &UserProfileTabController::onEnterTextForChangePassword);
    connect(mainWindow->editUserProfileNewRepeatPassword, &QLineEdit::textChanged,
            this, &UserProfileTabController::onEnterTextForChangePassword);
    connect(mainWindow->buttonChangePassword, &QPushButton::clicked,
            this, &UserProfileTabController::onTryChangePassword);

    connect(mainWindow->editPayAmount, &QLineEdit::textChanged,
            this, &UserProfileTabController::onEnterTextForPayMoney);
    connect(mainWindow->buttonPutMoney, &QPushButton::clicked,
            this, &UserProfileTabController::onTryPayMoney);

    mainWindow->editPayAmount->setValidator(new QDoubleValidator(0.01, 1000, 2));

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

    onUpdateUserInfo();

    mainWindow->editUserProfileNewLogin->setText("");
    mainWindow->editUserProfileNewPassword->setText("");
    mainWindow->editUserProfileNewRepeatPassword->setText("");
    mainWindow->editUserProfileOldPassword->setText("");
    mainWindow->editUserProfileUserPassword->setText("");
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

    mainWindow->labelUserProfileCashBackValue->setText(QString::number(user.cashback));
    mainWindow->labelUserProfileMoneyValue->setText(QString::number(user.money));
    mainWindow->labelUserProfilePersonalDiscountValue->setText(QString::number(user.personalDiscount));

    mainWindow->labelUserProfileNicknameValue->setText(user.nickname);
    mainWindow->labelUserProfileRoleValue->setText(user.role);
    mainWindow->labelUserProfileStatusValue->setText(user.status);

    loadUserDesiredGames();
}

void UserProfileTabController::onEnterTextForChangeLogin()
{
    bool oneFildIsEmpty = mainWindow->editUserProfileUserPassword->text().length() == 0 ||
                          mainWindow->editUserProfileNewLogin->text().length() == 0;

    if ( oneFildIsEmpty ) {
        mainWindow->buttonChangeLogin->setDisabled(true);
    }
    else {
        mainWindow->buttonChangeLogin->setEnabled(true);
    }
}

void UserProfileTabController::onEnterTextForChangePassword()
{
    bool oneFildIsEmpty = mainWindow->editUserProfileOldPassword->text().length() == 0 ||
                          mainWindow->editUserProfileNewPassword->text().length() == 0 ||
                          mainWindow->editUserProfileNewRepeatPassword->text().length() == 0;

    bool repeatPasswordEqualsNewPassword = mainWindow->editUserProfileNewPassword->text() ==
                                           mainWindow->editUserProfileNewRepeatPassword->text();

    if ( oneFildIsEmpty || !repeatPasswordEqualsNewPassword ) {
        mainWindow->buttonChangePassword->setDisabled(true);
    }
    else {
        mainWindow->buttonChangePassword->setEnabled(true);
    }
}

void UserProfileTabController::onTryChangeLogin()
{
    try {
        AccountController::get().changeLogin(mainWindow->editUserProfileNewLogin->text());
        mainWindow->editUserProfileNewLogin->setText("");
        mainWindow->editUserProfileUserPassword->setText("");
    }
    catch ( QString& errorMsg) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}

void UserProfileTabController::onTryChangePassword()
{
    try {
        AccountController::get().changePassword( mainWindow->editUserProfileOldPassword->text()
                                               , mainWindow->editUserProfileNewPassword->text());
        mainWindow->editUserProfileOldPassword->setText("");
        mainWindow->editUserProfileNewPassword->setText("");
        mainWindow->editUserProfileNewRepeatPassword->setText("");
    }
    catch ( QString& errorMsg) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}

void UserProfileTabController::onSelectDayInCalendar()
{

}

void UserProfileTabController::onEnterTextForPayMoney()
{
    if ( mainWindow->editPayAmount->text().length() > 0 ) {
        mainWindow->buttonPutMoney->setEnabled(true);
    }
    else {
        mainWindow->buttonPutMoney->setDisabled(true);
    }
}

void UserProfileTabController::onTryPayMoney()
{
    try {
        AccountController::get().putMoney(mainWindow->editPayAmount->text().toDouble());
        mainWindow->editPayAmount->setText("");
    }
    catch ( QString& errorMsg) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}

void UserProfileTabController::loadUserDesiredGames()
{
    mainWindow->listUserDesiredGames->clear();
    for ( auto& gameName : GameDatabaseController::getUserDesiredGameList(AccountController::get().user())) {
        new QListWidgetItem(gameName, mainWindow->listUserDesiredGames);
    }
}
