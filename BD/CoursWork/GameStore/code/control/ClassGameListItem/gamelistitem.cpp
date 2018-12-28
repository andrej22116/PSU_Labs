#include "gamelistitem.h"
#include "ui_gamelistitem.h"

#include <QGraphicsDropShadowEffect>
#include <code/control/ClassElidedLabel/elidedlabel.h>
#include <QVBoxLayout>

GameListItem::GameListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameListItem)
{
    ui->setupUi(this);

    this->setObjectName("GameListItem");

    auto effect = new QGraphicsDropShadowEffect(ui->centralWidget);
    effect->setOffset({0, 0});
    effect->setBlurRadius(32);
    effect->setColor(QColor(212, 255, 84));
    ui->labelCurrentCost->setGraphicsEffect(effect);

    labelGameName = new ElidedLabel(this);
    QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(ui->widgetLeft->layout());
    layout->insertWidget(0, labelGameName, 0, Qt::Alignment());
    labelGameName->setObjectName("labelGameName");
}

GameListItem::~GameListItem()
{
    delete ui;
    delete labelGameName;
}

void GameListItem::setGameInfo(const BaseGame &game)
{
    this->game = game;

    ui->labelDate->setText(game.dateOfReleaseGame.toString());
    labelGameName->setElidedText(game.gameName);

    if ( game.gameCost == 0 ) {
        ui->labelCurrentCost->setText("Free");
        ui->labelCostWithoutDiscount->hide();
    }
    else if ( game.discount > 0 ) {
        ui->labelCurrentCost->setText(QString("$%1").arg(game.gameCost - (game.gameCost * game.discount), 0, 'f', 2));
        ui->labelCostWithoutDiscount->setText(QString("$%1").arg(game.gameCost, 0, 'f', 2));
        ui->labelCostWithoutDiscount->show();
    }
    else {
        ui->labelCurrentCost->setText(QString("$%1").arg(game.gameCost, 0, 'f', 2));
        ui->labelCostWithoutDiscount->hide();
    }
}

const BaseGame& GameListItem::getGameInfo()
{
    return game;
}
