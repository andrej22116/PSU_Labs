#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QDate>
#include <QVector>

struct GameBase {
    QString gameName;
    QDate dateOfReleaseGame;
    double gameCost;
    float discount;
};

struct Game : public GameBase {
    QString gameDiscription;

    QString developerName;

    QVector<QString> genres;
    QVector<QString> tags;
    QVector<QString> devices;
};

#endif // GAME_H
