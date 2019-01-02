#include "commentarieswidget.h"
#include "ui_commentarieswidget.h"

#include "code/control/ClassMessenger/messenger.h"
#include "code/control/ClassAccountController/accountcontroller.h"
#include "code/control/ClassCommentaryWidget/commentarywidget.h"

#include <QScrollBar>

CommentariesWidget::CommentariesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentariesWidget)
{
    ui->setupUi(this);

    ui->listComments->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    connect(&AccountController::get(), &AccountController::userLoggedIn,
            this, &CommentariesWidget::onUserLogin);
    connect(&AccountController::get(), &AccountController::userLoggedOut,
            this, &CommentariesWidget::onUserLogout);

    connect(ui->buttonAddComment, &QPushButton::clicked,
            this, &CommentariesWidget::onAddNewComment);



    onUserLogout();
}

CommentariesWidget::~CommentariesWidget()
{
    delete ui;
}

void CommentariesWidget::setCommentariesLoader(const CommentariesWidget::CommentariesLoader& loader)
{
    this->commentsLoader = loader;
    updateCommentsList();
}

void CommentariesWidget::setCommentariesSender(const CommentariesWidget::CommentariesSender& sender)
{
    this->commentsSender = sender;
}

void CommentariesWidget::onAddNewComment()
{
    try {
        Commentary comment;
        comment.createTime = QDateTime::currentDateTime();
        comment.text = ui->textEditComment->toPlainText();

        commentsSender(comment);

        auto item = new QListWidgetItem(ui->listComments);
        auto commentItem = new CommentaryWidget(item, ui->listComments);
        commentItem->setCommentary(comment);

        ui->listComments->addItem(item);
        ui->listComments->setItemWidget(item, commentItem);

        ui->textEditComment->setPlainText("");
    }
    catch ( QString& errorMsg ) {
        Messenger::error(errorMsg, this);
    }
}

void CommentariesWidget::onNewCommentTextChanged()
{
    if ( ui->textEditComment->toPlainText().length() > 0 ) {
        ui->buttonAddComment->show();
    }
    else {
        ui->buttonAddComment->hide();
    }
}

void CommentariesWidget::onScrollToBack(int value)
{
    if ( listScrollBar->maximum() == value) {
        loadCommentsToList(20, loadedComments);
    }
}

void CommentariesWidget::onUserLogin()
{
    ui->widgetNewComment->show();
}

void CommentariesWidget::onUserLogout()
{
    ui->widgetNewComment->hide();
}

void CommentariesWidget::updateCommentsList()
{
    ui->listComments->clear();
    loadedComments = 0;

    loadCommentsToList(20, loadedComments);
}

void CommentariesWidget::loadCommentsToList(int limit, int offset)
{
    for ( auto& comment : commentsLoader(limit, offset)) {
        auto item = new QListWidgetItem(ui->listComments);
        auto commentItem = new CommentaryWidget(item, ui->listComments);
        commentItem->setCommentary(comment);

        ui->listComments->addItem(item);
        ui->listComments->setItemWidget(item, commentItem);

        ++loadedComments;
    }
}
