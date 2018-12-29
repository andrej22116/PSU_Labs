#ifndef COMMENTARYWIDGET_H
#define COMMENTARYWIDGET_H

#include <QWidget>

namespace Ui {
class CommentaryWidget;
}

class CommentaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentaryWidget(QWidget *parent = nullptr);
    ~CommentaryWidget();

private:
    Ui::CommentaryWidget *ui;
};

#endif // COMMENTARYWIDGET_H
