#include "librarytabcontroller.h"
#include "ui_mainwindow.h"
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include "code/control/ClassGameInfoWidget/gameinfowidget.h"
#include "code/control/ClassAccountController/accountcontroller.h"
#include "code/control/ClassMessenger/messenger.h"

#include <QListWidgetItem>
#include <QDebug>

LibraryTabController::LibraryTabController(Ui::MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    gameInfoWidget = new GameInfoWidget();
    mainWindow->widgetUserGameInfo->layout()->addWidget(gameInfoWidget);

    connect(&AccountController::get(), &AccountController::userLoggedIn,
            this, &LibraryTabController::onUserLogin);
    connect(&AccountController::get(), &AccountController::userLoggedOut,
            this, &LibraryTabController::onUserLogout);

    connect(mainWindow->listUserGames, &QListWidget::currentItemChanged,
            this, &LibraryTabController::onSelectUserGame);
}

LibraryTabController::~LibraryTabController()
{
    delete gameInfoWidget;
}

void LibraryTabController::onUserLogin()
{
    updateUserGameList();
}

void LibraryTabController::onUserLogout()
{
    //mainWindow->listUserGames->;
}

void LibraryTabController::updateUserGameList()
{
    try {
        auto userGames = GameDatabaseController::getUserGameNameList(AccountController::get().user());
        mainWindow->listUserGames->clear();

        for (auto& game : userGames) {
            new QListWidgetItem(game, mainWindow->listUserGames);
        }

        mainWindow->widgetUserGameInfo->hide();
    }
    catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}

void LibraryTabController::onSelectUserGame(QListWidgetItem* item)
{
    if ( !item ) { return; }
    try {
        BaseGame baseGame;
        baseGame.gameName = item->text();
        auto game = GameDatabaseController::getGameInfo(baseGame);
        gameInfoWidget->setExtendedGameInfo(game);
        mainWindow->widgetUserGameInfo->show();
    }
    catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, mainWindow->centralWidget->parentWidget());
    }
}
