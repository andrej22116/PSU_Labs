#ifndef USER_H
#define USER_H

#include <QString>

struct User {
    QString token;
    QString nickname;
    QString role;
    QString status;
};

#endif // USER_H
