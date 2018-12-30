#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "code/control/ClassGameListItem/gamelistitem.h"
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"

#include "code/control/ClassGameTabController/gametabcontroller.h"
#include "code/control/ClassUserProfileTabController/userprofiletabcontroller.h"
#include "code/control/ClassDevelopmentTabController/developmenttabcontroller.h"
#include "code/control/ClassGlobalNewsTabController/globalnewstabcontroller.h"
#include "code/control/ClassLibraryTabController/librarytabcontroller.h"

#include "code/control/ClassAccountController/accountcontroller.h"


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

    onUserLogout();

    connect(&AccountController::get(), &AccountController::userLoggedIn,
            this, &MainWindow::onUserLogin);
    connect(&AccountController::get(), &AccountController::userLoggedOut,
            this, &MainWindow::onUserLogout);

    AccountController::get().loadUserToken();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUserLogin()
{
    ui->mainTabWidget->addTab(ui->tabLibrary, ui->tabLibrary->windowIcon(), ui->tabLibrary->windowTitle());
    ui->mainTabWidget->addTab(ui->tabDevelopment, ui->tabDevelopment->windowIcon(), ui->tabDevelopment->windowTitle());
    ui->mainTabWidget->addTab(ui->tabUser, ui->tabUser->windowIcon(), AccountController::get().user().nickname);
}

void MainWindow::onUserLogout()
{
    int indexOfTabLibrary = ui->mainTabWidget->indexOf(ui->tabLibrary);
    ui->tabLibrary->setWindowTitle(ui->mainTabWidget->tabText(indexOfTabLibrary));
    ui->tabLibrary->setWindowIcon(ui->mainTabWidget->tabIcon(indexOfTabLibrary));
    ui->mainTabWidget->removeTab(indexOfTabLibrary);

    int indexOfTabDevelopment = ui->mainTabWidget->indexOf(ui->tabDevelopment);
    ui->tabDevelopment->setWindowTitle(ui->mainTabWidget->tabText(indexOfTabDevelopment));
    ui->tabDevelopment->setWindowIcon(ui->mainTabWidget->tabIcon(indexOfTabDevelopment));
    ui->mainTabWidget->removeTab(indexOfTabDevelopment);

    int indexOfTabUser = ui->mainTabWidget->indexOf(ui->tabUser);
    ui->tabUser->setWindowIcon(ui->mainTabWidget->tabIcon(indexOfTabUser));
    ui->mainTabWidget->removeTab(indexOfTabUser);
}
