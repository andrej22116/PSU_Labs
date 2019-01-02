#include "gametabcontroller.h"
#include "ui_mainwindow.h"

#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include "code/control/ClassGameListItem/gamelistitem.h"
#include "code/control/ClassGameInfoWidget/gameinfowidget.h"
#include "code/control/ClassMessenger/messenger.h"

#include "code/control/ClassAccountController/accountcontroller.h"

#include <QListWidgetItem>
#include <QScrollBar>
#include <QTextBrowser>

#include <QDebug>

GameTabController::GameTabController(Ui::MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    mainWindow->listGames->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    gameInfoWidget = new GameInfoWidget();
    mainWindow->widgetGameInfo->layout()->addWidget(gameInfoWidget);

    connect(&AccountController::get(), &AccountController::userLoggedIn,
            this, &GameTabController::onUserLogin);
    connect(&AccountController::get(), &AccountController::userLoggedOut,
            this, &GameTabController::onUserLogout);
    connect(&AccountController::get(), &AccountController::userUpdatedInfo,
            this, &GameTabController::onUpdateUserInfo);
    connect(mainWindow->listGames, &QListWidget::itemClicked,
            this, &GameTabController::onSelectGameItem);
    connect(mainWindow->buttonBuyGame, &QPushButton::clicked,
            this, &GameTabController::onBuyGame);
    connect(mainWindow->buttonAddToDesired, &QPushButton::clicked,
            this, &GameTabController::onAddToDesired);

    gameListScrollBar = mainWindow->listGames->verticalScrollBar();
    connect(gameListScrollBar, &QScrollBar::valueChanged, this, &GameTabController::onScrollToBack);

    mainWindow->widgetGameInfo->hide();

    onUpdateGameList();
}

GameTabController::~GameTabController()
{
    delete gameInfoWidget;
}

void GameTabController::onUpdateGameList()
{
    mainWindow->listGames->clear();
    loadGamesToList(20, 0);
}

void GameTabController::onScrollToBack(int value)
{
    if ( gameListScrollBar->maximum() == value) {
        loadGamesToList(20, mainWindow->listGames->count());
    }
}

void GameTabController::onSelectGameItem(QListWidgetItem *item)
{
    selectedGame = gameItemFromItem(item)->getGameInfo();

    try {
        auto game = GameDatabaseController::getGameInfo(selectedGame);
        mainWindow->widgetGameInfo->show();
        mainWindow->labelGameName->setText(game.gameName);
        if ( game.gameCost == 0 ) {
            mainWindow->labelGameCost->setText("FREE");
        }
        else if ( game.discount > 0 ) {
            mainWindow->labelGameCost->setText(
                        QString("<span style=\"text-decoration: line-through;\">$%1</span> $%2")
                        .arg(game.gameCost)
                        .arg(game.gameCost - game.gameCost * game.discount));
        }
        else {
            mainWindow->labelGameCost->setText(QString("$%1").arg(game.gameCost));
        }

        updateUserDependecy();

        gameInfoWidget->setExtendedGameInfo(game);
    }
    catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}

void GameTabController::onUserLogin()
{
    updateUserDependecy();
}

void GameTabController::onUserLogout()
{
    mainWindow->buttonBuyGame->hide();
}

void GameTabController::onUpdateUserInfo()
{
    updateUserDependecy();
}

void GameTabController::onBuyGame()
{
    try {
        AccountController::get().buyGame(selectedGame);

        new QListWidgetItem(selectedGame.gameName, mainWindow->listUserGames);
        mainWindow->buttonBuyGame->hide();
    }
    catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}

void GameTabController::onAddToDesired()
{
    try {
        AccountController::get().addGameToDesired(selectedGame);
    }
    catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
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
    } catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }

}

GameListItem* GameTabController::gameItemFromItem(QListWidgetItem* item)
{
    return dynamic_cast<GameListItem*>(mainWindow->listGames->itemWidget(item));
}

void GameTabController::updateUserDependecy()
{
    if ( AccountController::get().accountLevel() < 0 ) {
        mainWindow->buttonBuyGame->hide();
        mainWindow->buttonAddToDesired->hide();
        return;
    }

    bool userHaveNotThisGame = mainWindow->
                            listUserGames->
                            findItems(mainWindow->labelGameName->text(), Qt::MatchFlag::MatchContains).empty();
    if ( userHaveNotThisGame ) {
        mainWindow->buttonBuyGame->show();
    }
    else {
        mainWindow->buttonBuyGame->hide();
        mainWindow->buttonAddToDesired->hide();
        return;
    }

    double gameCost = selectedGame.gameCost - selectedGame.gameCost * selectedGame.discount;

    bool userWantThisGame = mainWindow->
                            listUserDesiredGames->
                            findItems(mainWindow->labelGameName->text(), Qt::MatchFlag::MatchContains).count() > 0;
    if ( userHaveNotThisGame && !userWantThisGame && gameCost > 0) {
        mainWindow->buttonAddToDesired->setEnabled(true);
    }
    else {
        mainWindow->buttonAddToDesired->setDisabled(true);
    }

    if ( AccountController::get().user().money >= gameCost) {
        mainWindow->buttonBuyGame->setEnabled(true);
    }
    else {
        mainWindow->buttonBuyGame->setDisabled(true);
    }

}
