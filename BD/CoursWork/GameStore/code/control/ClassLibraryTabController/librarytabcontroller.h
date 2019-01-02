#ifndef LIBRARYTABCONTROLLER_H
#define LIBRARYTABCONTROLLER_H

#include <QObject>

namespace Ui {
class MainWindow;
}

class QListWidgetItem;
class GameInfoWidget;

class LibraryTabController : public QObject
{
    Q_OBJECT

public:
    LibraryTabController(Ui::MainWindow* mainWindow);
    ~LibraryTabController() override;
    LibraryTabController(const LibraryTabController&) = delete;
    LibraryTabController(LibraryTabController&&) = delete;
    LibraryTabController& operator = (const LibraryTabController&) = delete;
    LibraryTabController& operator = (LibraryTabController&&) = delete;

private slots:
    void onUserLogin();
    void onUserLogout();

    void updateUserGameList();

    void onSelectUserGame(QListWidgetItem* item);

private:
    Ui::MainWindow* mainWindow;
    GameInfoWidget* gameInfoWidget;
};

#endif // LIBRARYTABCONTROLLER_H
