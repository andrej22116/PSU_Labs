#ifndef USERPROFILETABCONTROLLER_H
#define USERPROFILETABCONTROLLER_H

#include <QObject>
#include <QVector>
#include "code/model/purchase.h"

namespace Ui {
class MainWindow;
}

class LoginWidget;
class RegistrationWidget;

class UserProfileTabController : public QObject
{
    Q_OBJECT

public:
    UserProfileTabController(Ui::MainWindow* mainWindow);
    ~UserProfileTabController() override;
    UserProfileTabController(const UserProfileTabController&) = delete;
    UserProfileTabController(UserProfileTabController&&) = delete;
    UserProfileTabController& operator = (const UserProfileTabController&) = delete;
    UserProfileTabController& operator = (UserProfileTabController&&) = delete;

public slots:
    void onUserLogin();
    void onUserLogout();
    void onUpdateUserInfo();

    void onEnterTextForChangeLogin();
    void onEnterTextForChangePassword();

    void onTryChangeLogin();
    void onTryChangePassword();

    void onSelectDayInCalendar();

    void onEnterTextForPayMoney();
    void onTryPayMoney();

private:
    void loadUserDesiredGames();

private:
    Ui::MainWindow* mainWindow;
    LoginWidget* loginDialog;
    RegistrationWidget* registrationDialog;
    QVector<Purchase> userPurchases;
};

#endif // USERPROFILETABCONTROLLER_H
