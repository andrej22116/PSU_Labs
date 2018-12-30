#include "userdatabasecontroller.h"

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

const QString UserDatabaseController::templateQueryRegistration{
    "select public_function_registration('%1', '%2', '%3');"
};

void UserDatabaseController::registration(const QString& userLogin, const QString& userPassword, const QString& userNickname)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryRegistration.arg(userLogin).arg(userPassword).arg(userNickname);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryLogin{"select public_function_login('%1', '%2');"};

CurrentUser UserDatabaseController::login(const QString& userLogin, const QString& userPassword)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryLogin.arg(userLogin).arg(userPassword);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    CurrentUser user;
    if ( query.next() ) {
        user.token = query.value(0).toString();
    }

    updateCurrentUserInfo(user);

    return user;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryLogout{"select public_function_logout('%1');"};

void UserDatabaseController::logout(const CurrentUser& user)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryLogout.arg(user.token);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryTestToken{"select public_function_test_token('%1');"};

bool UserDatabaseController::isAuthorized(const CurrentUser& user)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryTestToken.arg(user.token);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    bool authorized;
    if ( query.next() ) {
        authorized = query.value(0).toBool();
    }

    return authorized;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryChangeLogin{"select public_function_update_login('%1', '%2');"};

void UserDatabaseController::changeLogin(const CurrentUser& user, const QString& newUserLogin)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryChangeLogin.arg(user.token).arg(newUserLogin);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryChangePassword{
    "select public_function_update_password('%1', '%2', '%3');"
};

void UserDatabaseController::changePassword(const CurrentUser& user, const QString& oldUserPassword,
                                            const QString& newUserPassword)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryChangePassword.arg(user.token).arg(oldUserPassword).arg(newUserPassword);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryChangeNickname{".................."};

void UserDatabaseController::changeNickname(const CurrentUser& user, const QString& newUserNickname)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryPutMoney{"select public_function_put_money('%1', '%2');"};

void UserDatabaseController::putMoney(const CurrentUser& user, double money)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryPutMoney.arg(user.token).arg(money);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryUpdateCurrentUserInfo{
    "select * from public_function_get_current_user_info('%1');"
};

void UserDatabaseController::updateCurrentUserInfo(CurrentUser& user)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryTestToken.arg(user.token);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    if ( query.next() ) {
        user.nickname = query.value(0).toString();
        user.role = query.value(1).toString();
        user.status = query.value(2).toString();
        user.money = query.value(3).toDouble();
        user.cashback = query.value(4).toDouble();
        user.personalDiscount = query.value(5).toDouble();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryGetUserInfo{"................................."};

User UserDatabaseController::getUserInfo()
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString UserDatabaseController::templateQueryDeleteAccount{"select public_function_delete_account('%1');"};

void UserDatabaseController::deleteAccount(const CurrentUser& user)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryDeleteAccount.arg(user.token);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}


