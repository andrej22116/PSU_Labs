#include "postgresqlview.h"
#include <QtSql>

PostgreSqlView::PostgreSqlView(const PostgreSqlView &pgSqlView) noexcept
{
    dbName_ = pgSqlView.dbName_;
    serverPort_ = pgSqlView.serverPort_;
    serverUrl_ = pgSqlView.serverUrl_;
    userLogin_ = pgSqlView.userLogin_;
    userPassword_ = pgSqlView.userPassword_;
}

void PostgreSqlView::setConnectInfo(const QString& url, int databasePort,
                                    const QString& password) noexcept
{
    serverUrl_ = url;
    serverPort_ = databasePort;
    userLogin_ = "postgres";
    userPassword_ = password;
    dbName_ = "postgres";
}

void PostgreSqlView::setConnectInfo(const QString& url, int databasePort,
                        const QString& login, const QString& password) noexcept
{
    serverUrl_ = url;
    serverPort_ = databasePort;
    userLogin_ = login;
    userPassword_ = password;
    dbName_ = "postgres";
}

void PostgreSqlView::setConnectInfo(const QString& url, int databasePort,
                                    const QString& dbName, const QString& login,
                                    const QString& password) noexcept
{
    serverUrl_ = url;
    serverPort_ = databasePort;
    userLogin_ = login;
    userPassword_ = password;
    dbName_ = dbName;
}

DbList PostgreSqlView::getDatabasesList()
{
    static const QString queryTemplateGetDatabases =
            "select pg_database.datname"
            "from pg_database"
            "where pg_database.datistemplate = false;";

    const QString connectionName = getDatabaseConnectionName(dbName_);
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    if ( !query.exec(queryTemplateGetDatabases) ) {
        disconnectFromDatabase(connectionName);
        throw QString("Error on exec get databases list query!");
    }

    DbList resultList;
    QSqlRecord record = query.record();
    int indexOfColumn = record.indexOf("datname");
    while ( query.next() ) {
        resultList.push_back(query.value(indexOfColumn).toString());
    }

    disconnectFromDatabase(connectionName);

    return resultList;
}

SchemasList PostgreSqlView::getDatabaseSchemasList(const QString& databaseName)
{
    static const QString queryTemplateGetSchemas =
            "select schemata.schema_name"
            "from information_schema.schemata schemata;";

    const QString connectionName = getDatabaseConnectionName(databaseName);
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    if ( !query.exec(queryTemplateGetSchemas) ) {
        disconnectFromDatabase(connectionName);
        throw QString("Error on exec get database schemas list query!");
    }

    SchemasList resultList;
    QSqlRecord record = query.record();
    int indexOfColumn = record.indexOf("schema_name");
    while ( query.next() ) {
        resultList.push_back(query.value(indexOfColumn).toString());
    }

    disconnectFromDatabase(connectionName);

    return resultList;
}

TablesList PostgreSqlView::getDatabaseSchemaTablesList(
        const QString& databaseName, const QString& schemaName)
{
    static const QString queryTemplateGetSchemaTables =
            "select t_table.table_name"
            "from information_schema.tables t_table"
            "where t_table.table_schema = '%1';";

    const QString connectionName = getDatabaseConnectionName(databaseName);
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    if ( !query.exec(queryTemplateGetSchemaTables.arg(schemaName)) ) {
        disconnectFromDatabase(connectionName);
        throw QString("Error on exec get database schema tables list query!");
    }

    TablesList resultList;
    QSqlRecord record = query.record();
    int indexOfColumn = record.indexOf("table_name");
    while ( query.next() ) {
        resultList.push_back(query.value(indexOfColumn).toString());
    }

    disconnectFromDatabase(connectionName);

    return resultList;
}

ColumnsList PostgreSqlView::getDatavaseSchemaTableColumnsList(
        const QString& databaseName, const QString& schemaName,
        const QString& tableName)
{
    static const QString queryTemplateGetSchemaTableColumns =
            "select t_columns.column_name"
            "from information_schema.columns t_columns"
            "where t_columns.table_schema = '%1'"
            "and t_columns.table_name = '%2';";

    const QString connectionName = getDatabaseConnectionName(databaseName);
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    bool isError = !query.exec(queryTemplateGetSchemaTableColumns
                               .arg(schemaName)
                               .arg(tableName));
    if ( isError ) {
        disconnectFromDatabase(connectionName);
        throw QString("Error on exec get database schema "
                      "table columns list query!");
    }

    ColumnsList resultList;
    QSqlRecord record = query.record();
    int indexOfColumn = record.indexOf("column_name");
    while ( query.next() ) {
        resultList.push_back(query.value(indexOfColumn).toString());
    }

    disconnectFromDatabase(connectionName);

    return resultList;
}

FunctionsList PostgreSqlView::getDatabaseFunctionsList(
        const QString& databaseName, const QString& schemaName)
{
    static const QString queryTemplateGetSchemaFunctions =
            "select routines.routine_name"
            "from information_schema.routines"
            "where routines.specific_schema = '%1';";

    const QString connectionName = getDatabaseConnectionName(databaseName);
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    if ( !query.exec(queryTemplateGetSchemaFunctions.arg(schemaName)) ) {
        disconnectFromDatabase(connectionName);
        throw QString("Error on exec get database "
                      "schema functions list query!");
    }

    FunctionsList resultList;
    QSqlRecord record = query.record();
    int indexOfColumn = record.indexOf("routine_name");
    while ( query.next() ) {
        resultList.push_back(query.value(indexOfColumn).toString());
    }

    disconnectFromDatabase(connectionName);

    return resultList;
}

FunctionParametersList PostgreSqlView::getDatabaseFunctionParametersList(
        const QString& databaseName, const QString& schemaName,
        const QString& functionName)
{
    static const QString queryTemplateGetSchemaFunctionParameters =
            "select parameters.parameter_mode, parameters.data_type"
            "from information_schema.routines"
            "left join information_schema.parameters"
            "on routines.specific_name = parameters.specific_name"
            "where routines.specific_schema = '%1'"
            "and routines.routine_name = '%2'"
            "order by routines.routine_name, parameters.ordinal_position;";

    const QString connectionName = getDatabaseConnectionName(databaseName);
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    bool isError = !query.exec(queryTemplateGetSchemaFunctionParameters
                              .arg(schemaName)
                              .arg(functionName));
    if ( isError ) {
        disconnectFromDatabase(connectionName);
        throw QString("Error on exec get database "
                      "schema function parameters list query!");
    }

    FunctionParametersList resultList;
    QSqlRecord record = query.record();
    int indexOfColumnMode = record.indexOf("parameter_mode");
    int indexOfColumnType = record.indexOf("data_type");
    while ( query.next() ) {
        QString item = query.value(indexOfColumnMode).toString() +
                " " + query.value(indexOfColumnType).toString();
        resultList.push_back(item);
    }

    disconnectFromDatabase(connectionName);

    return resultList;
}

QString PostgreSqlView::getDatabaseConnectionName(const QString &databaseName)
{
    QString connectionName = serverUrl_ + ":" + serverPort_ + databaseName;
    QSqlDatabase connection = QSqlDatabase::addDatabase("QPSQL", connectionName);

    if ( !connection.isValid() ) {
        throw QString("Problems with the QPSQL driver!");
    }

    connection.setDatabaseName(databaseName);
    connection.setHostName(serverUrl_);
    connection.setPort(serverPort_);

    if ( !connection.open(userLogin_, userPassword_) ) {
        throw QString("Problems with connect to database!");
    }

    return connectionName;
}

void PostgreSqlView::disconnectFromDatabase(const QString &connectionName)
{
    QSqlDatabase::removeDatabase(connectionName);
}
