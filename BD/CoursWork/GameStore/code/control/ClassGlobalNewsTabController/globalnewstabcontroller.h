#ifndef GLOBALNEWSTABCONTROLLER_H
#define GLOBALNEWSTABCONTROLLER_H

#include <QObject>

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class GlobalNewsTabController : public QObject
{

public:
    GlobalNewsTabController(Ui::MainWindow* mainWindow);
    ~GlobalNewsTabController() override = default;
    GlobalNewsTabController(const GlobalNewsTabController&) = delete;
    GlobalNewsTabController(GlobalNewsTabController&&) = delete;
    GlobalNewsTabController& operator = (const GlobalNewsTabController&) = delete;
    GlobalNewsTabController& operator = (GlobalNewsTabController&&) = delete;

private slots:
    void onSelectTab(int index);
    void onUpdateGameList();
    void onSelectGameListItem(QListWidgetItem* item);

private:
    void loadGames(int limit, int offset);

private:
    Ui::MainWindow* mainWindow{};
};

#endif // GLOBALNEWSTABCONTROLLER_H
