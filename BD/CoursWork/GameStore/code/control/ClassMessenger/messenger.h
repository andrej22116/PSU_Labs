#ifndef MESSENGER_H
#define MESSENGER_H

#include <QWidget>

class Messenger
{
public:
    Messenger() = delete;
    ~Messenger() = delete;
    Messenger(const Messenger&) = delete;
    Messenger(Messenger&&) = delete;
    Messenger& operator = (const Messenger&) = delete;
    Messenger& operator = (Messenger&&) = delete;

    static void error(const QString& message, QWidget* parent = nullptr);
};

#endif // MESSENGER_H
