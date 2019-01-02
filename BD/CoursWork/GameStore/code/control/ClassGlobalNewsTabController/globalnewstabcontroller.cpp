#include "globalnewstabcontroller.h"
#include "ui_mainwindow.h"

#include "code/control/ClassGameListItem/gamelistitem.h"
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"

#include <QListWidgetItem>

GlobalNewsTabController::GlobalNewsTabController(Ui::MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void GlobalNewsTabController::onSelectTab(int)
{
    if ( mainWindow->mainTabWidget->currentWidget() != mainWindow->tabGameStore ) {
        return;
    }

    if ( mainWindow->listGames->count() == 0 ) {
        loadGames(20, 0);
    }
}

void GlobalNewsTabController::onUpdateGameList()
{
    mainWindow->listGames->clear();
    loadGames(20, 0);
}

void GlobalNewsTabController::onSelectGameListItem(QListWidgetItem* item)
{
    GameListItem* gameItem = dynamic_cast<GameListItem*>(mainWindow->listGames->itemWidget(item));
    mainWindow->statusBar->showMessage(gameItem->getGameInfo().gameName);
}

void GlobalNewsTabController::loadGames(int limit, int offset)
{
    for (auto& game : GameDatabaseController::getGameList(limit, offset)) {
        auto findedItems = mainWindow->listGames->findItems(game.gameName, Qt::MatchFlag::MatchContains);
        if ( findedItems.length() == 1 ) {
            GameListItem* gameItem = dynamic_cast<GameListItem*>(mainWindow->listGames->itemWidget(findedItems[0]));
            gameItem->setGameInfo(game);
            continue;
        }

        auto gameItem = new GameListItem();
        gameItem->setGameInfo(game);

        auto listItem = new QListWidgetItem(game.gameName, mainWindow->listGames);
        listItem->setSizeHint(gameItem->sizeHint());

        mainWindow->listGames->addItem(listItem);
        mainWindow->listGames->setItemWidget(listItem, gameItem);
    }
}
