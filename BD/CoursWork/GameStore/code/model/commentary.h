#ifndef COMMENTARY_H
#define COMMENTARY_H

#include <QString>
#include <QUuid>
#include <QDateTime>

struct Commentary {
    QString userNickname;
    QDateTime createTime;
    QDateTime modifyTime;
    QString text;
    QUuid id;
};

#endif // COMMENTARY_H
