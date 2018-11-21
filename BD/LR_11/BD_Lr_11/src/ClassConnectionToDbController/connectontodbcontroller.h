#ifndef CONNECTONTODBCONTROLLER_H
#define CONNECTONTODBCONTROLLER_H

#include <QObject>

class ConnectonToDbController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString database READ database WRITE setDatabase NOTIFY databaseChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    explicit ConnectonToDbController(QObject *parent = nullptr);

    QString login();
    void setLogin(const QString& login);

    QString password();
    void setPassword(const QString& password);

    QString host();
    void setHost(const QString& host);

    QString port();
    void setPort(const QString& port);

    QString database();
    void setDatabase(const QString& database);

    QString status();



signals:
    void loginChanged();
    void passwordChanged();
    void hostChanged();
    void portChanged();
    void databaseChanged();
    void statusChanged();

public slots:
    bool onConnectHandler();

private:
    void setStatus(const QString& status);

    QString _login;
    QString _password;
    QString _host;
    QString _port;
    QString _database;
    QString _connectionName;
    QString _status;
};

#endif // CONNECTONTODBCONTROLLER_H
