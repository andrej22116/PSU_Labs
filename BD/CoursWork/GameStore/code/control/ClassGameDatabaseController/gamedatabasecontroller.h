#ifndef GAMEDATABASECONTROLLER_H
#define GAMEDATABASECONTROLLER_H


#include <QVector>
#include "code/model/game.h"
#include "code/model/developer.h"
#include "code/model/game_addon.h"
#include "code/model/game_statistic.h"
#include "code/model/user.h"

class GameDatabaseController
{
    static const QString templateQueryGetGameList;
    static const QString templateQueryGetGameAddonList;
    static const QString templateQueryGetUserGameNameList;
    static const QString templateQueryBuyGame;
    static const QString templateQueryBuyGameForUser;
    static const QString templateQueryBuyGameAddon;
    static const QString templateQueryAddGame;
    static const QString templateQueryAddGameAddon;
    static const QString templateQueryGetGameNobodyBoughtList;
    static const QString templateQueryGetGameInfo;
    static const QString templateQueryGetGameStatistic;
    static const QString templateQueryGetFullGameStatisticList;
    static const QString templateQueryAddGameToDesiredGames;
    static const QString templateQueryLockGame;
    static const QString templateQueryUnlockGame;

public:
    GameDatabaseController() = delete;
    ~GameDatabaseController() = delete;
    GameDatabaseController(const GameDatabaseController&) = delete;
    GameDatabaseController(const GameDatabaseController&&) = delete;
    GameDatabaseController& operator = (const GameDatabaseController&) = delete;
    GameDatabaseController& operator = (const GameDatabaseController&&) = delete;


    static QVector<BaseGame> getGameList(int amount, int offset);
    static QVector<GameAddon> getGameAddonList(const BaseGame& game);
    static QVector<QString> getUserGameNameList(const CurrentUser& user);

    static void buyGame(const CurrentUser& user, const BaseGame& game);
    static void buyGameForUser(const CurrentUser& user, const BaseUser& targetUser, const BaseGame& game);
    static void buyGameAddon(const CurrentUser& user, const GameAddon& gameAddon);

    static void addGame(const CurrentUser& user, const Game& game);
    static void addGameAddon(const CurrentUser& user, const GameAddon& gameAddon);

    static QVector<BaseGame> getGameNobodyBoughtList(int amount, int offset);

    static Game getGameInfo(const BaseGame& game);
    static GameStatistic getGameStatistic(const CurrentUser& user, const BaseGame& game, int year);
    static QVector<GameStatistic> getFullGameStatisticList(const CurrentUser& user, const BaseGame& game);

    static void addGameToDesiredGames(const CurrentUser& user, const BaseGame& game);

    static void lockGame(const CurrentUser& user,  const BaseGame& game);
    static void unlockGame(const CurrentUser& user,  const BaseGame& game);

};

#endif // GAMEDATABASECONTROLLER_H
