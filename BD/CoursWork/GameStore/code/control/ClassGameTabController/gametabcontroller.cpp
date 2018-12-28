#include "gametabcontroller.h"
#include "ui_mainwindow.h"

#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include "code/control/ClassGameListItem/gamelistitem.h"

#include <QListWidgetItem>

GameTabController::GameTabController(Ui::MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;

    connect(mainWindow->mainTabWidget, &QTabWidget::currentChanged, this, &GameTabController::onSelectTab);
    connect(mainWindow->listGames, &QListWidget::itemClicked, this, &GameTabController::onSelectGameItem);
}

void GameTabController::onSelectTab(int index)
{
    if ( mainWindow->mainTabWidget->currentWidget() != mainWindow->tabGameStore ) {
        return;
    }

    if ( mainWindow->listGames->count() == 0 ) {
        loadGamesToList(20, 0);
    }
}

void GameTabController::onUpdateGameList()
{
    mainWindow->listGames->clear();
    loadGamesToList(20, 0);
}

void GameTabController::onSelectGameItem(QListWidgetItem *item)
{
    auto gameItem = gameItemFromItem(item);
    mainWindow->statusBar->showMessage(gameItem->getGameInfo().gameName);
}

void GameTabController::loadGamesToList(int limit, int offset)
{
    for (auto& game : GameDatabaseController::getGameList(limit, offset)) {
        auto findResult = mainWindow->listGames->findItems(game.gameName, Qt::MatchFlag::MatchContains);
        if ( findResult.length() == 1 ) {
            auto gameItem = gameItemFromItem(findResult[0]);
            gameItem->setGameInfo(game);
            continue;
        }

        auto gameItem = new GameListItem(mainWindow->listGames);
        gameItem->setGameInfo(game);

        auto item = new QListWidgetItem(mainWindow->listGames);
        item->setSizeHint(gameItem->sizeHint());

        mainWindow->listGames->addItem(item);
        mainWindow->listGames->setItemWidget(item, gameItem);
    }
}

GameListItem* GameTabController::gameItemFromItem(QListWidgetItem* item)
{
    return dynamic_cast<GameListItem*>(mainWindow->listGames->itemWidget(item));
}
