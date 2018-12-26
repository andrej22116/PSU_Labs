#ifndef NEWS_H
#define NEWS_H

#include <QString>
#include <QDateTime>
#include <QUuid>

struct News {
    QDateTime createTime;
    QDateTime modifyTime;
    QString text;
    QString title;
    QString authorNickname;
    QUuid id;
};

#endif // NEWS_H
