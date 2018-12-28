#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QStyledItemDelegate>

#include "code/control/ClassGameListItem/gamelistitem.h"
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"

#include "code/control/ClassGameTabController/gametabcontroller.h"
#include "code/control/ClassUserProfileTabController/userprofiletabcontroller.h"
#include "code/control/ClassDevelopmentTabController/developmenttabcontroller.h"
#include "code/control/ClassGlobalNewsTabController/globalnewstabcontroller.h"
#include "code/control/ClassLibraryTabController/librarytabcontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gameTabController = std::make_shared<GameTabController>(ui);
    userProfileTabController = std::make_shared<UserProfileTabController>(ui);
    developmentTabController = std::make_shared<DevelopmentTabController>(ui);
    globalNewsTabController = std::make_shared<GlobalNewsTabController>(ui);
    libraryTabController = std::make_shared<LibraryTabController>(ui);

    /*
    for (auto game : GameDatabaseController::getGameList(99, 0)) {
        auto item = new QListWidgetItem(ui->listGames);
        auto gameWidget = new GameListItem();
        item->setSizeHint(gameWidget->sizeHint());
        gameWidget->setGameInfo(game);

        ui->listGames->addItem(item);
        ui->listGames->setItemWidget(item, gameWidget);
    }
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
