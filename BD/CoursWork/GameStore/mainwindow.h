#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameTabController;
class UserProfileTabController;
class DevelopmentTabController;
class GlobalNewsTabController;
class LibraryTabController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::shared_ptr<GameTabController> gameTabController;
    std::shared_ptr<UserProfileTabController> userProfileTabController;
    std::shared_ptr<DevelopmentTabController> developmentTabController;
    std::shared_ptr<GlobalNewsTabController> globalNewsTabController;
    std::shared_ptr<LibraryTabController> libraryTabController;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onUserLogin();
    void onUserLogout();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
