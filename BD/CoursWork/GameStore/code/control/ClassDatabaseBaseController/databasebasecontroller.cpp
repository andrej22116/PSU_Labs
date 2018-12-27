#include "databasebasecontroller.h"

bool DatabaseBaseController::connected = false;
QString DatabaseBaseController::lastError{"No error!"};
const QString DatabaseBaseController::databaseName{"GameStore"};
const QString DatabaseBaseController::connectionDatabaseName{"GameStoreConnect"};

QSqlDatabase DatabaseBaseController::getConnection()
{
    return QSqlDatabase::database(connectionDatabaseName);
}


const QString& DatabaseBaseController::getConnectionName()
{
    return connectionDatabaseName;
}


const QString& DatabaseBaseController::getLastError()
{
    return lastError;
}


bool DatabaseBaseController::isConnected()
{
    return connected;
}


bool DatabaseBaseController::connect()
{
    if ( QSqlDatabase::contains(connectionDatabaseName) ) {
        return true;
    }

    if ( !QSqlDatabase::isDriverAvailable("QPSQL") ) {
        lastError = "Driver isn't available!";
        connected = false;
        return connected;
    }

    auto connection = QSqlDatabase::addDatabase("QPSQL", connectionDatabaseName);
    connection.setDatabaseName(databaseName);
    connection.setHostName("localhost");
    connection.setPort(5432);

    if ( !connection.open("user", "user") ) {
        lastError = "Could not connect to server!";
        connected = false;
        return connected;
    }

    connected = true;
    return connected;
}
