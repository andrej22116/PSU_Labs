#include "commentarywidget.h"
#include "ui_commentarywidget.h"

#include "code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h"
#include "code/control/ClassAccountController/accountcontroller.h"

#include <QListWidgetItem>
#include <QMessageBox>

#include <QDebug>

CommentaryWidget::CommentaryWidget(QListWidgetItem* item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentaryWidget)
{
    ui->setupUi(this);
    this->item = item;

    connect(&AccountController::get(), &AccountController::userLoggedIn,
            this, &CommentaryWidget::onUserLogin);
    connect(&AccountController::get(), &AccountController::userLoggedOut,
            this, &CommentaryWidget::onUserLogout);
    connect(ui->buttonModify, &QPushButton::clicked,
            this, &CommentaryWidget::onModifyCommentary);
    connect(ui->buttonDelete, &QPushButton::clicked,
            this, &CommentaryWidget::onDeleteCommentary);
    connect(ui->buttonSave, &QPushButton::clicked,
            this, &CommentaryWidget::onSaveModifyCommentary);
    connect(ui->buttonCancel, &QPushButton::clicked,
            this, &CommentaryWidget::onCancelModifyCommentary);

    onUserLogout();
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

    setDefaultState();
}

const Commentary& CommentaryWidget::getCommentary()
{
    return comment;
}

void CommentaryWidget::onDeleteCommentary()
{
    try {
        CommentsDatabaseController::deleteCommentaryForGame(AccountController::get().user(), comment);
        delete item;
        delete this;
    }
    catch ( QString& errorMsg ) {
        qDebug() << errorMsg;
    }
}

void CommentaryWidget::onModifyCommentary()
{
    ui->comment->setReadOnly(false);
    ui->widgetModifyButtons->show();
    ui->buttonModify->hide();

    updateCommentSize();
}

void CommentaryWidget::onSaveModifyCommentary()
{
    try {
        Commentary comment =   this->comment;
        comment.text = ui->comment->toPlainText();
        CommentsDatabaseController::modifyCommentaryForGame(AccountController::get().user(), comment);

        this->comment.text = comment.text;
        this->comment.modifyTime = QDateTime::currentDateTime();

        ui->labelModifyDate->setText(this->comment.modifyTime.toString());

        ui->comment->setReadOnly(true);

        ui->widgetModifyButtons->hide();
        ui->buttonModify->show();

        setDefaultState();
    }
    catch ( QString& errorMsg ) {
        QMessageBox errorMsgDialog(this);
        errorMsgDialog.setModal(true);
        errorMsgDialog.setWindowTitle("Ошибка!");
        errorMsgDialog.setText(errorMsg);
        errorMsgDialog.setIcon(QMessageBox::Icon::Critical);
        errorMsgDialog.exec();
    }
}

void CommentaryWidget::onCancelModifyCommentary()
{
    ui->comment->setText(comment.text);
    setDefaultState();
}

void CommentaryWidget::onUserLogin()
{
    auto user = AccountController::get().user();
    auto level = AccountController::get().accountLevel();
    bool isUserComment = user.nickname == comment.userNickname;

    if ( level > 0 || isUserComment ) {
        ui->buttonDelete->show();
    }
    if ( isUserComment ) {
        ui->buttonModify->show();
        ui->labelUserNickname->setStyleSheet("font-weight: bold;");
    }

    ui->widgetModifyButtons->hide();
}

void CommentaryWidget::onUserLogout()
{
    ui->widgetModifyButtons->hide();
    ui->buttonDelete->hide();
    ui->buttonModify->hide();
    ui->labelUserNickname->setStyleSheet("");
    ui->comment->setReadOnly(true);
}

void CommentaryWidget::setDefaultState()
{
    ui->comment->setReadOnly(true);

    auto level = AccountController::get().accountLevel();
    if ( level >= 0 ) {
        onUserLogin();
    }
    else {
        onUserLogout();
    }

    updateCommentSize();
}

void CommentaryWidget::updateCommentSize()
{
    ui->comment->document()->adjustSize();
    ui->comment->setFixedHeight( ui->comment->document()->size().height() );
    item->setSizeHint(this->sizeHint());
}
