#include "commentarywidget.h"
#include "ui_commentarywidget.h"

CommentaryWidget::CommentaryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentaryWidget)
{
    ui->setupUi(this);
}

CommentaryWidget::~CommentaryWidget()
{
    delete ui;
}
