#include "gameinfowidget.h"
#include "ui_gameinfowidget.h"

#include "code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h"
#include "code/control/ClassAccountController/accountcontroller.h"
#include "code/control/ClassMessenger/messenger.h"
#include "code/control/ClassCommentariesWidget/commentarieswidget.h"

#include <QListWidgetItem>

GameInfoWidget::GameInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameInfoWidget)
{
    ui->setupUi(this);

    connect(ui->textGameDescription, &QTextBrowser::textChanged,
            this, &GameInfoWidget::onSetGameDescription );

    commentaries = new CommentariesWidget();
    commentaries->setCommentariesLoader([this](int limit, int offset) {
        return CommentsDatabaseController::getGameCommetaries(game, limit, offset);
    });
    commentaries->setCommentariesSender([this](Commentary& comment) {
        auto user = AccountController::get().user();
        comment.userNickname = user.nickname;
        CommentsDatabaseController::addNewCommentaryForGame(user, game, comment);
    });
    ui->tabComments->layout()->addWidget(commentaries);
}

GameInfoWidget::~GameInfoWidget()
{
    delete ui;
    delete commentaries;
}

const ExtendedGame& GameInfoWidget::getExtendedGameInfo()
{
    return game;
}

void GameInfoWidget::setExtendedGameInfo(const ExtendedGame &game)
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

    ui->labelDateOfRelease->setText(game.dateOfReleaseGame.toString());

    commentaries->updateCommentsList();
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
