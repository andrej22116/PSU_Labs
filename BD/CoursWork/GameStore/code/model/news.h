#ifndef NEWS_H
#define NEWS_H

#include <QString>
#include <QDateTime>
#include <QUuid>

struct BaseNews {
    QUuid id;
    QString title;
    QString authorNickname;
    QDateTime createTime;
    QDateTime modifyTime;
};

struct News : public BaseNews {
    QString text;
};

#endif // NEWS_H
