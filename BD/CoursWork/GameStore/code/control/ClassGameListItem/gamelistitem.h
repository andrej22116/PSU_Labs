#ifndef GAMELISTITEM_H
#define GAMELISTITEM_H

#include <QWidget>
#include "code/model/game.h"

namespace Ui {
class GameListItem;
}

class ElidedLabel;

class GameListItem : public QWidget
{
    Q_OBJECT

    ElidedLabel* labelGameName;
    BaseGame game;

public:
    explicit GameListItem(QWidget *parent = nullptr);
    ~GameListItem();

    void setGameInfo(const BaseGame& game);
    const BaseGame& getGameInfo();

private:
    Ui::GameListItem *ui;
};

#endif // GAMELISTITEM_H
