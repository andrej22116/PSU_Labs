#ifndef USERDATABASECONTROLLER_H
#define USERDATABASECONTROLLER_H

#include "code/model/user.h"

class UserDatabaseController
{
    static const QString templateQueryRegistration;
    static const QString templateQueryLogin;
    static const QString templateQueryLogout;
    static const QString templateQueryTestToken;
    static const QString templateQueryChangeLogin;
    static const QString templateQueryChangePassword;
    static const QString templateQueryChangeNickname;
    static const QString templateQueryPutMoney;
    static const QString templateQueryUpdateCurrentUserInfo;
    static const QString templateQueryGetUserInfo;
    static const QString templateQueryDeleteAccount;

public:
    UserDatabaseController() = delete;
    ~UserDatabaseController() = delete;
    UserDatabaseController(const UserDatabaseController&) = delete;
    UserDatabaseController(const UserDatabaseController&&) = delete;
    UserDatabaseController& operator = (const UserDatabaseController&) = delete;
    UserDatabaseController& operator = (const UserDatabaseController&&) = delete;

    static void registration(const QString& userLogin, const QString& userPassword, const QString& userNickname);
    static CurrentUser login(const QString& userLogin, const QString& userPassword);
    static void logout(CurrentUser& user);

    static bool isAuthorized(const CurrentUser& user);

    static void changeLogin(const CurrentUser& user, const QString& newUserLogin);
    static void changePassword(const CurrentUser& user, const QString& oldUserPassword, const QString& newUserPassword);
    static void changeNickname(const CurrentUser& user, const const QString& newUserNickname);

    static void putMoney(CurrentUser& user, double money);
    static void updateCurrentUserInfo(CurrentUser& user);
    static User getUserInfo();

    static void deleteAccount(const CurrentUser& user);
};

#endif // USERDATABASECONTROLLER_H
