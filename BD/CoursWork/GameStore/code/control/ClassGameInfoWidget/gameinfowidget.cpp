#include "gameinfowidget.h"
#include "ui_gameinfowidget.h"

#include <code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h>
#include <code/control/ClassCommentaryWidget/commentarywidget.h>

#include <QListWidgetItem>

GameInfoWidget::GameInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameInfoWidget)
{
    ui->setupUi(this);

    connect( ui->textGameDescription, &QTextBrowser::textChanged,
             this, &GameInfoWidget::onSetGameDescription );
}

GameInfoWidget::~GameInfoWidget()
{
    delete ui;
}

const ExtendedGame& GameInfoWidget::getExtendedGameInfo()
{
    return game;
}

void GameInfoWidget::setExtendedGameInfo(const ExtendedGame& game)
{
    this->game = game;
    ui->textGameDescription->setText(game.gameDiscription);

    ui->listTags->clear();
    for ( auto& tag : game.tags ) {
        auto item = new QListWidgetItem(tag, ui->listTags);
        ui->listTags->addItem(item);
    }

    ui->listGenres->clear();
    for ( auto& genre : game.genres ) {
        auto item = new QListWidgetItem(genre, ui->listGenres);
        ui->listGenres->addItem(item);
    }

    ui->textEditComment->setPlainText("");

    updateCommentsList();
}

void GameInfoWidget::resizeEvent(QResizeEvent *event)
{
    onSetGameDescription();
}

void GameInfoWidget::onSetGameDescription()
{
      QSize size = ui->textGameDescription->document()->size().toSize();
      ui->textGameDescription->setFixedHeight( std::max(400, size.height() + 20) );
}

void GameInfoWidget::updateCommentsList()
{
    ui->listComments->clear();
    loadGameCommentsToList(20, 0);
}

void GameInfoWidget::loadGameCommentsToList(int limit, int offset)
{
    for ( auto& comment : CommentsDatabaseController::getGameCommetaries(game, limit, offset)) {
        auto item = new QListWidgetItem(ui->listComments);
        auto commentItem = new CommentaryWidget(item, ui->listComments);
        commentItem->setCommentary(comment);

        ui->listComments->addItem(item);
        ui->listComments->setItemWidget(item, commentItem);
    }
}
