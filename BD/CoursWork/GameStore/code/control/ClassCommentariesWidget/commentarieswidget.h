#ifndef COMMENTARIESWIDGET_H
#define COMMENTARIESWIDGET_H

#include <QWidget>
#include <functional>

#include "code/model/commentary.h"

namespace Ui {
class CommentariesWidget;
}

class QScrollBar;

class CommentariesWidget : public QWidget
{
    Q_OBJECT

public:
    using CommentariesLoader = std::function<QVector<Commentary>(int limit, int offset)>;
    using CommentariesSender = std::function<void(Commentary&)>;

    explicit CommentariesWidget(QWidget *parent = nullptr);
    ~CommentariesWidget() override;

    void setCommentariesLoader(const CommentariesLoader& loader);
    void setCommentariesSender(const CommentariesSender& sender);

    void updateCommentsList();

private slots:
    void onUserLogin();
    void onUserLogout();

    void onAddNewComment();
    void onNewCommentTextChanged();

    void onScrollToBack(int value);

private:
    void loadCommentsToList(int limit, int offset);

private:
    int loadedComments = 0;
    Ui::CommentariesWidget *ui;
    QScrollBar* listScrollBar;
    CommentariesLoader commentsLoader = [](int, int){ return QVector<Commentary>(); };
    CommentariesSender commentsSender = [](Commentary&){};
};

#endif // COMMENTARIESWIDGET_H
