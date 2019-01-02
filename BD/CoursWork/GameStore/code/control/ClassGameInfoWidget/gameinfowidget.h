#ifndef GAMEINFOWIDGET_H
#define GAMEINFOWIDGET_H

#include <QWidget>
#include "code/model/game.h"


class QResizeEvent;
class CommentariesWidget;

namespace Ui {
class GameInfoWidget;
}

class GameInfoWidget : public QWidget
{
    Q_OBJECT

    ExtendedGame game;

public:
    explicit GameInfoWidget(QWidget *parent = nullptr);
    ~GameInfoWidget();

    const ExtendedGame& getExtendedGameInfo();
    void setExtendedGameInfo(const ExtendedGame& game);

protected:
    void resizeEvent(QResizeEvent* event) override;

protected slots:
    void onSetGameDescription();

private:
    Ui::GameInfoWidget *ui;
    CommentariesWidget* commentaries;
};

#endif // GAMEINFOWIDGET_H
