#ifndef COMMENTARYWIDGET_H
#define COMMENTARYWIDGET_H

#include <QWidget>
#include "code./model/commentary.h"

class QListWidgetItem;

namespace Ui {
class CommentaryWidget;
}

class CommentaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentaryWidget(QListWidgetItem* item, QWidget *parent = nullptr);
    ~CommentaryWidget();

    void setCommentary(const Commentary& comment);
    const Commentary& getCommentary();

signals:
    void deleteCommentary(QListWidgetItem* item);

protected slots:
    void onDeleteCommentary();
    void onModifyCommentary();
    void onSaveModifyCommentary();
    void onCancelModifyCommentary();

    void onUserLogin();
    void onUserLogout();

private:
    void setDefaultState();
    void updateCommentSize();

private:
    Ui::CommentaryWidget *ui;
    Commentary comment;
    QListWidgetItem* item;
};

#endif // COMMENTARYWIDGET_H
