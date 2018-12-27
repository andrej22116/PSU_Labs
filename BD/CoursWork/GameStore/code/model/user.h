#ifndef USER_H
#define USER_H

#include <QString>

struct BaseUser {
    QString nickname;
};

struct User : public BaseUser {
    QString role;
    QString status;
};

struct CurrentUser : public User {
    QString token;
    double money;
    double cashback;
    double personalDiscount;
};

#endif // USER_H
