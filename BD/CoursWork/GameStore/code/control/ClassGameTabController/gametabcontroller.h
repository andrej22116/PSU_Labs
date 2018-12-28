#ifndef GAMETABCONTROLLER_H
#define GAMETABCONTROLLER_H

#include <QObject>

namespace Ui {
class MainWindow;
}

class QListWidgetItem;
class GameListItem;

class GameTabController : public QObject
{
public:
    GameTabController(Ui::MainWindow* mainWindow);
    ~GameTabController() = default;
    GameTabController(const GameTabController&) = delete;
    GameTabController(GameTabController&&) = delete;
    GameTabController& operator = (const GameTabController&) = delete;
    GameTabController& operator = (GameTabController&&) = delete;

private slots:
    void onSelectTab(int index);
    void onUpdateGameList();
    void onSelectGameItem(QListWidgetItem* item);

private:
    void loadGamesToList(int limit, int offset);
    GameListItem* gameItemFromItem(QListWidgetItem* item);

private:
    Ui::MainWindow* mainWindow;

};

#endif // GAMETABCONTROLLER_H
