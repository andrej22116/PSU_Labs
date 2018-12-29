#ifndef GAMETABCONTROLLER_H
#define GAMETABCONTROLLER_H

#include <QObject>

namespace Ui {
class MainWindow;
}

class QListWidgetItem;
class GameListItem;
class QScrollBar;
class GameInfoWidget;

class GameTabController : public QObject
{
public:
    GameTabController(Ui::MainWindow* mainWindow);
    ~GameTabController() override;
    GameTabController(const GameTabController&) = delete;
    GameTabController(GameTabController&&) = delete;
    GameTabController& operator = (const GameTabController&) = delete;
    GameTabController& operator = (GameTabController&&) = delete;

private slots:
    void onSelectTab(int index);
    void onUpdateGameList();
    void onScrollToBack(int value);
    void onSelectGameItem(QListWidgetItem* item);

private:
    void loadGamesToList(int limit, int offset);
    GameListItem* gameItemFromItem(QListWidgetItem* item);

private:
    Ui::MainWindow* mainWindow;
    QScrollBar* gameListScrollBar;
    GameInfoWidget* gameInfoWidget;
};

#endif // GAMETABCONTROLLER_H
