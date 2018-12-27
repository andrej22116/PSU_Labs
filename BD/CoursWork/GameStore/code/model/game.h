#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QDate>
#include <QVector>

struct BaseGame {
    QString gameName;
    QDate dateOfReleaseGame;
    double gameCost;
    float discount;
};

struct Game : public BaseGame {
    QString gameDiscription;
    QString developerName;
};

struct ExtendedGame : public Game {
    QVector<QString> genres;
    QVector<QString> tags;
    QVector<QString> devices;
};

#endif // GAME_H
