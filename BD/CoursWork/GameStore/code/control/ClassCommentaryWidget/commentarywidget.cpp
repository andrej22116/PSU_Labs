#include "commentarywidget.h"
#include "ui_commentarywidget.h"

#include "code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h"

#include <QListWidgetItem>

#include <QDebug>

CommentaryWidget::CommentaryWidget(QListWidgetItem* item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentaryWidget)
{
    ui->setupUi(this);
    this->item = item;

    setDefaultState();
}

CommentaryWidget::~CommentaryWidget()
{
    delete ui;
}

void CommentaryWidget::setCommentary(const Commentary& comment)
{
    this->comment = comment;
    ui->comment->setPlainText(comment.text);
    ui->labelCreateDate->setText(comment.createTime.toString());
    ui->labelModifyDate->setText(comment.modifyTime.toString());
    ui->labelUserNickname->setText(comment.userNickname);

    updateCommentSize();
}

const Commentary& CommentaryWidget::getCommentary()
{
    return comment;
}

void CommentaryWidget::onDeleteCommentary()
{

}

void CommentaryWidget::onModifyCommentary()
{
    ui->comment->setReadOnly(false);
    ui->widgetModifyButtons->show();
    updateCommentSize();
}

void CommentaryWidget::onSaveModifyCommentary()
{
    comment.text = ui->comment->toPlainText();
    //CommentsDatabaseController::modifyCommentaryForGame(, comment);

    setDefaultState();
}

void CommentaryWidget::onCancelModifyCommentary()
{
    ui->comment->setText(comment.text);
    setDefaultState();
}

void CommentaryWidget::setDefaultState()
{
    ui->comment->setReadOnly(true);
    ui->widgetModifyButtons->hide();

    updateCommentSize();
}

void CommentaryWidget::updateCommentSize()
{
    ui->comment->document()->adjustSize();
    qDebug() << ui->comment->document()->size();
    ui->comment->setFixedHeight( ui->comment->document()->size().height() );
    item->setSizeHint(this->sizeHint());
}
