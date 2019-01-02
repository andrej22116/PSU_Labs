#ifndef GAMETABCONTROLLER_H
#define GAMETABCONTROLLER_H

#include <QObject>
#include "code/model/game.h"

namespace Ui {
class MainWindow;
}

class QListWidgetItem;
class GameListItem;
class QScrollBar;
class GameInfoWidget;

class GameTabController : public QObject
{
public:
    GameTabController(Ui::MainWindow* mainWindow);
    ~GameTabController() override;
    GameTabController(const GameTabController&) = delete;
    GameTabController(GameTabController&&) = delete;
    GameTabController& operator = (const GameTabController&) = delete;
    GameTabController& operator = (GameTabController&&) = delete;

private slots:
    void onUpdateGameList();
    void onScrollToBack(int value);
    void onSelectGameItem(QListWidgetItem* item);

    void onUserLogin();
    void onUserLogout();
    void onUpdateUserInfo();

    void onBuyGame();
    void onAddToDesired();

private:
    void loadGamesToList(int limit, int offset);
    GameListItem* gameItemFromItem(QListWidgetItem* item);
    void updateUserDependecy();

private:
    Ui::MainWindow* mainWindow;
    QScrollBar* gameListScrollBar;
    GameInfoWidget* gameInfoWidget;
    BaseGame selectedGame;
};

#endif // GAMETABCONTROLLER_H
