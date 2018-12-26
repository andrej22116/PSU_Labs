#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDateTime>
#include <QString>
#include <QUuid>

struct Purchase {
    QDateTime dateTime;
    QString discription;
    double cost;
    QString userNickname;
    QUuid id;
};

#endif // PURCHASE_H
