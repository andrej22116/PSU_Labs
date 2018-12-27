#ifndef DATABASEBASECONTROLLER_H
#define DATABASEBASECONTROLLER_H

//#include <QString>
#include <QSqlDatabase>

class DatabaseBaseController {
    static bool connected;
    static const QString databaseName;
    static const QString connectionDatabaseName;
    static QString lastError;

public:
    DatabaseBaseController() = delete;
    ~DatabaseBaseController() = delete;
    DatabaseBaseController(const DatabaseBaseController&) = delete;
    DatabaseBaseController(const DatabaseBaseController&&) = delete;
    DatabaseBaseController& operator = (const DatabaseBaseController&) = delete;
    DatabaseBaseController& operator = (const DatabaseBaseController&&) = delete;

    static QSqlDatabase getConnection();
    static const QString& getConnectionName();
    static const QString& getLastError();
    static bool isConnected();

    static bool connect();
};

#endif // DATABASEBASECONTROLLER_H
