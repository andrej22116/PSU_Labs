#include "connectontodbcontroller.h"
#include <QtSql>

ConnectonToDbController::ConnectonToDbController(QObject *parent) : QObject(parent)
{

}

QString ConnectonToDbController::login()
{
    return _login;
}

void ConnectonToDbController::setLogin(const QString &login)
{
    if ( _login == login ) { return; }

    _login = login;
    emit loginChanged();
}

QString ConnectonToDbController::password()
{
    return _password;
}

void ConnectonToDbController::setPassword(const QString &password)
{
    if ( _password == password ) { return; }

    _password = password;
    emit passwordChanged();
}

QString ConnectonToDbController::host()
{
    return _host;
}

void ConnectonToDbController::setHost(const QString &host)
{
    if ( _host == host ) { return; }

    _host = host;
    emit hostChanged();
}

QString ConnectonToDbController::port()
{
    return _port;
}

void ConnectonToDbController::setPort(const QString &port)
{
    if ( _port == port ) { return; }

    _port = port;
    emit portChanged();
}

QString ConnectonToDbController::database()
{
    return _database;
}

void ConnectonToDbController::setDatabase(const QString &database)
{
    if ( _database == database ) { return; }

    _database = database;
    emit databaseChanged();
}

QString ConnectonToDbController::status()
{
    return _status;
}

bool ConnectonToDbController::onConnectHandler()
{
    //auto newDatabase = QSqlConnection();
    _connectionName = QString("%1:%2?database=%3&login=%4")
            .arg(_host).arg(_port).arg(_database).arg(_login);

    auto database = QSqlDatabase::addDatabase("QPSQL", _connectionName);
    if ( !database.isValid() ) {
        setStatus(database.lastError().text());
        _connectionName = "";
        return false;
    }

    bool isValidInteger = true;
    int port = _port.toInt(&isValidInteger);
    if ( !isValidInteger ) {
        setStatus(database.lastError().text());
        _connectionName = "";
        return false;
    }

    database.setHostName(_host);
    database.setPort(port);
    database.setDatabaseName(_database);
    if ( !database.open(_login, _password) ) {
        setStatus(database.lastError().text());
        QSqlDatabase::removeDatabase(_connectionName);
        _connectionName = "";
        return false;
    }

    setStatus(_connectionName);
    return true;
}

void ConnectonToDbController::setStatus(const QString &status)
{
    _status = status;
    emit statusChanged();
}
