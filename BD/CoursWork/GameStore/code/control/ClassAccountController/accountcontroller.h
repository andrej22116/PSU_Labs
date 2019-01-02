#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include "code/model/user.h"
#include "code/model/game.h"
#include "code/model/game_addon.h"

#include <QObject>

class AccountController : public QObject
{    
    Q_OBJECT

public:
    enum AccountLevel {
        LevelNoUser = -1,
        LevelUser = 0,
        LevelModerator = 1,
        LevelAdministrator = 2
    };

private:
    CurrentUser user_;
    AccountLevel accountLevel_ = LevelUser;
    const QString userTokenPath = "user/token";

public:

    static AccountController& get();

    void registration(const QString& login, const QString& password, const QString& nickname);
    void login(const QString& login, const QString& password);
    void login(const QString& token);
    void logout();

    void setUserToken(const QString& token);
    const QString& userToken();
    bool isAuthorized();
    bool isValidToken();

    AccountLevel accountLevel() { return accountLevel_; }
    bool isModerator() { return accountLevel_ == LevelModerator; }
    bool isAdministrator() { return accountLevel_ == LevelAdministrator; }

    const CurrentUser& user() { return user_; }

    void changeLogin(const QString& newLogin);
    void changePassword(const QString& oldPassword, const QString& newPassword);

    void updateUserInfo();

    void saveUserToken();
    void loadUserToken();

    void putMoney(double amount);
    void buyGame(const BaseGame& game);
    void buyGameAddon(const GameAddon& gameAddon);
    void buyDeveloperStatus();

    void addGameToDesired(const BaseGame& game);

signals:
    void userLoggedIn();
    void userLoggedOut();
    void userUpdatedInfo();

private:
    AccountController() = default;
};

#endif // ACCOUNTCONTROLLER_H
