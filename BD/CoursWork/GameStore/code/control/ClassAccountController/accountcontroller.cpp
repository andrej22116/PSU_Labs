#include "accountcontroller.h"

#include "code/control/ClassUserDatabaseController/userdatabasecontroller.h"
#include <QSettings>

AccountController& AccountController::get()
{
    static AccountController controller;
    return controller;
}

void AccountController::registration(const QString& login, const QString& password, const QString& nickname)
{
    UserDatabaseController::registration(login, password, nickname);
    user_ = UserDatabaseController::login(login, password);
}

void AccountController::login(const QString& login, const QString& password)
{
    user_ = UserDatabaseController::login(login, password);
    saveUserToken();
    emit userLoggedIn();
}

void AccountController::login(const QString& token)
{
    user_.token = token;
    if ( isAuthorized() ) {
        UserDatabaseController::updateCurrentUserInfo(user_);
        saveUserToken();
        emit userLoggedIn();
    }
    else {
        user_.token = "";
    }
}

void AccountController::logout()
{
    UserDatabaseController::logout(user_);
    user_.token = "";
    emit userLoggedOut();
}

void AccountController::setUserToken(const QString& token)
{
    user_.token = token;
}

const QString &AccountController::userToken()
{
    return user_.token;
}

bool AccountController::isAuthorized()
{
    return UserDatabaseController::isAuthorized(user_);
}

bool AccountController::isValidToken()
{
    return UserDatabaseController::isAuthorized(user_);
}

void AccountController::changeLogin(const QString &newLogin)
{
    UserDatabaseController::changeLogin(user_, newLogin);
}

void AccountController::changePassword(const QString &oldPassword, const QString &newPassword)
{
    UserDatabaseController::changePassword(user_, oldPassword, newPassword);
}

void AccountController::updateUserInfo()
{
    UserDatabaseController::updateCurrentUserInfo(user_);
    emit userUpdatedInfo();
}

void AccountController::saveUserToken()
{
    QSettings settings{};
    settings.setValue(userTokenPath, user_.token);
    settings.sync();
}

void AccountController::loadUserToken()
{
    QSettings settings{};
    QString userToken = settings.value(userTokenPath, "").toString();
    if ( userToken.length() > 0 ) {
        login(userToken);
    }
}

