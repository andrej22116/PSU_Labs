#include "gametabcontroller.h"
#include "ui_mainwindow.h"

#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include "code/control/ClassGameListItem/gamelistitem.h"
#include "code/control/ClassGameInfoWidget/gameinfowidget.h"

#include <QListWidgetItem>
#include <QScrollBar>
#include <QTextBrowser>

#include <QDebug>

GameTabController::GameTabController(Ui::MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;

    gameInfoWidget = new GameInfoWidget();
    mainWindow->widgetGameInfo->layout()->addWidget(gameInfoWidget);

    connect(mainWindow->mainTabWidget, &QTabWidget::currentChanged, this, &GameTabController::onSelectTab);
    connect(mainWindow->listGames, &QListWidget::itemClicked, this, &GameTabController::onSelectGameItem);

    gameListScrollBar = mainWindow->listGames->verticalScrollBar();
    connect(gameListScrollBar, &QScrollBar::valueChanged, this, &GameTabController::onScrollToBack);
}

GameTabController::~GameTabController()
{
    delete gameInfoWidget;
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

void GameTabController::onScrollToBack(int value)
{
    if ( gameListScrollBar->maximum() == value && mainWindow->listGames->count() % 20 == 0) {
        loadGamesToList(20, mainWindow->listGames->count());
    }
}

void GameTabController::onSelectGameItem(QListWidgetItem *item)
{
    auto gameItem = gameItemFromItem(item);
    //mainWindow->statusBar->showMessage(gameItem->getGameInfo().gameName);

    try {
        auto game = GameDatabaseController::getGameInfo(gameItem->getGameInfo());
        mainWindow->labelGameCost->setText(QString("$%1").arg(game.gameCost));

        gameInfoWidget->setExtendedGameInfo(game);
    }
    catch ( QString& errorMessage ) {
        qDebug() << errorMessage;
    }
}

void GameTabController::loadGamesToList(int limit, int offset)
{
    try {
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
    } catch ( QString& errorMessage ) {
        qDebug() << errorMessage;
    }

}

GameListItem* GameTabController::gameItemFromItem(QListWidgetItem* item)
{
    return dynamic_cast<GameListItem*>(mainWindow->listGames->itemWidget(item));
}
