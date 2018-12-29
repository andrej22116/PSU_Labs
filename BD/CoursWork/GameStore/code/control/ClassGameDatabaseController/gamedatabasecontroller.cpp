#include "gamedatabasecontroller.h"

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>


const QString GameDatabaseController::templateQueryGetGameList{
    "select * from public_function_get_game_list('%1', '%2');"
};

QVector<BaseGame> GameDatabaseController::getGameList(int amount, int offset)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryGetGameList.arg(amount).arg(offset);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    QVector<BaseGame> result;
    while ( query.next() ) {
        result.push_back({
            query.value(0).toString(),
            query.value(3).toDate(),
            query.value(1).toDouble(),
            query.value(2).toFloat()
        });
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryGetGameAddonList{
    "select * from public_function_get_game_addons('%1');"
};

QVector<GameAddon> GameDatabaseController::getGameAddonList(const BaseGame& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryGetGameAddonList.arg(game.gameName);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    QVector<GameAddon> result;
    while ( query.next() ) {
        result.push_back({
            game.gameName,
            query.value(0).toString(),
            query.value(1).toDouble(),
            query.value(2).toString()
        });
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryGetUserGameNameList{
    "select * from public_function_get_user_games('%1');"
};

QVector<QString> GameDatabaseController::getUserGameNameList(const CurrentUser& user)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryGetUserGameNameList.arg(user.token);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    QVector<QString> result;
    while ( query.next() ) {
        result.push_back(query.value(0).toString());
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryBuyGame{"select public_function_buy_game('%1', '%2');"};

void GameDatabaseController::buyGame(const CurrentUser& user, const BaseGame& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryBuyGame.arg(user.token).arg(game.gameName);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryBuyGameForUser{"select public_function_buy_game ......"};

void GameDatabaseController::buyGameForUser(const CurrentUser& user, const BaseUser& targetUser, const BaseGame& game)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryBuyGameAddon{
    "select public_function_buy_game_addon('%1', '%2', '%3');"
};

void GameDatabaseController::buyGameAddon(const CurrentUser& user, const GameAddon& gameAddon)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryBuyGameAddon.arg(user.token).arg(gameAddon.currentGameName).arg(gameAddon.name);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryAddGame{"select public_function_add_game('%1', '%2', '%3', '%4');"};

void GameDatabaseController::addGame(const CurrentUser& user, const Game& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryAddGame
            .arg(user.token)
            .arg(game.gameName)
            .arg(game.gameCost)
            .arg(game.gameDiscription);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryAddGameAddon{
    "select public_function_add_game_addon('%1', '%2', '%3', '%4', '%5');"
};

void GameDatabaseController::addGameAddon(const CurrentUser& user, const GameAddon& gameAddon)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryAddGameAddon
            .arg(user.token)
            .arg(gameAddon.currentGameName)
            .arg(gameAddon.name)
            .arg(gameAddon.cost)
            .arg(gameAddon.discription);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryGetGameNobodyBoughtList{
    "select * from public_function_get_games_nobody_bought('%1', '%2');"
};

QVector<BaseGame> GameDatabaseController::getGameNobodyBoughtList(int amount, int offset)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryGetGameNobodyBoughtList.arg(amount).arg(offset);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    QVector<BaseGame> result;
    while ( query.next() ) {
        result.push_back({
            query.value(0).toString(),
            query.value(3).toDate(),
            query.value(1).toDouble(),
            query.value(2).toFloat()
        });
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryGetGameInfo{
    "select * from public_function_get_full_game_info('%1');"
};

ExtendedGame GameDatabaseController::getGameInfo(const BaseGame& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryGetGameInfo.arg(game.gameName);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    auto parceStringArray = [](const QString& stringArray, QVector<QString>& target) {
        QStringRef stringRef(&stringArray, 1, stringArray.length() - 2);
        QVector<QStringRef> stringRefSplitVector = stringRef.split(",");
        for (auto& ref : stringRefSplitVector) {
            QString item = ref.toString();

            if ( item.length() > 0 ) {
                target << item;
            }
        }
    };

    ExtendedGame gameInfo;
    while ( query.next() ) {
        gameInfo.gameName = query.value(0).toString();
        gameInfo.gameCost = query.value(1).toDouble();
        gameInfo.discount = query.value(2).toFloat();
        gameInfo.dateOfReleaseGame = query.value(3).toDate();
        gameInfo.gameDiscription = query.value(4).toString();
        gameInfo.developerName = query.value(5).toString();

        parceStringArray(query.value(6).toString(), gameInfo.genres);
        parceStringArray(query.value(7).toString(), gameInfo.tags);
        parceStringArray(query.value(8).toString(), gameInfo.devices);
    }

    return gameInfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryGetGameStatistic{"select * from ........"};

GameStatistic GameDatabaseController::getGameStatistic(const CurrentUser& user, const BaseGame& game, int year)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryGetFullGameStatisticList{"select * from ............."};

QVector<GameStatistic> GameDatabaseController::getFullGameStatisticList(const CurrentUser& user, const BaseGame& game)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryAddGameToDesiredGames{
    "select public_function_add_game_to_desired_games('%1', '%2');"
};

void GameDatabaseController::addGameToDesiredGames(const CurrentUser& user, const BaseGame& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryAddGameToDesiredGames
            .arg(user.token)
            .arg(game.gameName);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryLockGame{"select public_function_lock_game('%1', '%2');"};

void GameDatabaseController::lockGame(const CurrentUser& user,  const BaseGame& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryLockGame
            .arg(user.token)
            .arg(game.gameName);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString GameDatabaseController::templateQueryUnlockGame{"select public_function_unlock_game('%1', '%2');"};

void GameDatabaseController::unlockGame(const CurrentUser& user,  const BaseGame& game)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryUnlockGame
            .arg(user.token)
            .arg(game.gameName);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

