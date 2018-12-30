#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include "code/model/user.h"

class AccountController
{    
public:
    enum AccountLevel {
        LevelUser = 0,
        LevelModerator = 1,
        LevelAdministrator = 2
    };

private:
    CurrentUser user_;
    AccountLevel accountLevel_ = LevelUser;

public:

    static AccountController& get();

    void registration(const QString& login, const QString& password, const QString& nickname);
    void login(const QString& login, const QString& password);
    void logout();

    void setUserToken(const QString& token);
    const QString& userToken();
    bool isAuthorized();

    AccountLevel accountLevel() { accountLevel_; }
    bool isModerator() { return accountLevel_ == LevelModerator; }
    bool isAdministrator() { return accountLevel_ == LevelAdministrator; }

    const CurrentUser& user() { return user_; }

    void changeLogin(const QString& newLogin);
    void changePassword(const QString& oldPassword, const QString& newPassword);

    void updateUserInfo();

private:
    AccountController() = default;
};

#endif // ACCOUNTCONTROLLER_H
