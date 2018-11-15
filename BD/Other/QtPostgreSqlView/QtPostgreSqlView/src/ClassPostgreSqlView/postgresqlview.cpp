#include "postgresqlview.h"
#include <QtSql>
#include <QTableView>

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
            "select pg_database.datname as \"datname\" "
            "from pg_database "
            "where pg_database.datistemplate = false;";

    const QString connectionName = getDatabaseConnectionName(dbName_);

    SchemasList resultList = makeListWithNamesFromQuery(
            connectionName,
            queryTemplateGetDatabases,
            [](QSqlRecord record) -> QString {
                return record.value("datname").toString();
            },
            [this, &connectionName]() {
                disconnectFromDatabase(connectionName);
                throw QString("Error on exec get databases list query!");
            }
        );

    disconnectFromDatabase(connectionName);

    return resultList;
}

SchemasList PostgreSqlView::getDatabaseSchemasList(const QString& databaseName)
{
    static const QString queryTemplateGetSchemas =
            "select schemata.schema_name "
            "from information_schema.schemata schemata;";

    const QString connectionName = getDatabaseConnectionName(databaseName);

    SchemasList resultList = makeListWithNamesFromQuery(
            connectionName,
            queryTemplateGetSchemas,
            [](QSqlRecord record) -> QString {
                return record.value("schema_name").toString();
            },
            [this, &connectionName]() {
                disconnectFromDatabase(connectionName);
                throw QString("Error on exec get database "
                              "schemas list query!");
            }
        );

    disconnectFromDatabase(connectionName);

    return resultList;
}

TablesList PostgreSqlView::getDatabaseSchemaTablesList(
        const QString& databaseName, const QString& schemaName)
{
    static const QString queryTemplateGetSchemaTables =
            "select t_table.table_name "
            "from information_schema.tables t_table "
            "where t_table.table_schema = '%1';";

    const QString connectionName = getDatabaseConnectionName(databaseName);

    const QString queryString = queryTemplateGetSchemaTables
                                .arg(schemaName);

    TablesList resultList = makeListWithNamesFromQuery(
            connectionName,
            queryString,
            [](QSqlRecord record) -> QString {
                return record.value("table_name").toString();
            },
            [this, &connectionName]() {
                disconnectFromDatabase(connectionName);
                throw QString("Error on exec get database "
                              "schema tables list query!");
            }
        );

    disconnectFromDatabase(connectionName);

    return resultList;
}

ColumnsList PostgreSqlView::getDatabaseSchemaTableColumnsList(
        const QString& databaseName, const QString& schemaName,
        const QString& tableName)
{
    static const QString queryTemplateGetSchemaTableColumns =
            "select t_columns.column_name "
            "from information_schema.columns t_columns "
            "where t_columns.table_schema = '%1' "
            "and t_columns.table_name = '%2';";

    const QString connectionName = getDatabaseConnectionName(databaseName);

    const QString queryString = queryTemplateGetSchemaTableColumns
                                .arg(schemaName)
                                .arg(tableName);

    ColumnsList resultList = makeListWithNamesFromQuery(
            connectionName,
            queryString,
            [](QSqlRecord record) -> QString {
                return record.value("column_name").toString();
            },
            [this, &connectionName]() {
                disconnectFromDatabase(connectionName);
                throw QString("Error on exec get database schema "
                              "table columns list query!");
            }
        );

    disconnectFromDatabase(connectionName);

    return resultList;
}

FunctionsList PostgreSqlView::getDatabaseFunctionsList(
        const QString& databaseName, const QString& schemaName)
{
    static const QString queryTemplateGetSchemaFunctions =
            "select routines.routine_name "
            "from information_schema.routines "
            "where routines.specific_schema = '%1';";

    const QString connectionName = getDatabaseConnectionName(databaseName);

    const QString queryString = queryTemplateGetSchemaFunctions
                                .arg(schemaName);

    FunctionsList resultList = makeListWithNamesFromQuery(
            connectionName,
            queryString,
            [](QSqlRecord record) -> QString {
                return record.value("routine_name").toString();
            },
            [this, &connectionName]() {
                disconnectFromDatabase(connectionName);
                throw QString("Error on exec get database "
                              "schema functions list query!");
            }
        );

    disconnectFromDatabase(connectionName);

    return resultList;
}

FunctionParametersList PostgreSqlView::getDatabaseFunctionParametersList(
        const QString& databaseName, const QString& schemaName,
        const QString& functionName)
{
    static const QString queryTemplateGetSchemaFunctionParameters =
            "select parameters.parameter_mode, parameters.data_type "
            "from information_schema.routines "
            "left join information_schema.parameters "
            "on routines.specific_name = parameters.specific_name "
            "where routines.specific_schema = '%1' "
            "and routines.routine_name = '%2' "
            "order by routines.routine_name, parameters.ordinal_position;";

    const QString connectionName = getDatabaseConnectionName(databaseName);
    const QString queryString = queryTemplateGetSchemaFunctionParameters
                          .arg(schemaName)
                          .arg(functionName);

    FunctionParametersList resultList = makeListWithNamesFromQuery(
            connectionName,
            queryString,
            [](QSqlRecord record) -> QString {
                QString item = record.value("parameter_mode").toString() +
                        " " + record.value("data_type").toString();
                return item;
            },
            [this, &connectionName]() {
                disconnectFromDatabase(connectionName);
                throw QString("Error on exec get database "
                              "schema function parameters list query!");
            }
        );

    disconnectFromDatabase(connectionName);

    return resultList;
}

QSqlTableModel* PostgreSqlView::getSqlTableModel( QTableView* tableView,
        const QString &databaseName, const QString&, const QString &tableName)
{
    QString connectionName = getDatabaseConnectionName(databaseName, "TableView");
    QSqlDatabase database = QSqlDatabase::database(connectionName);

    QSqlTableModel* model = new QSqlTableModel(tableView, database);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    //model->setTable(database.driver()->escapeIdentifier(tableName, QSqlDriver::TableName));
    model->select();
    if (model->lastError().type() != QSqlError::NoError) {
        throw "Error: " + model->lastError().text();
    }

    return model;
}

QString PostgreSqlView::getDatabaseConnectionName(const QString &databaseName)
{
    return getDatabaseConnectionName(databaseName, "");
}

QString PostgreSqlView::getDatabaseConnectionName(const QString &databaseName, const QString &postfix)
{
    QString connectionName = QString("%1:%2/%3#%4")
                             .arg(serverUrl_)
                             .arg(serverPort_)
                             .arg(databaseName)
                             .arg(postfix);
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

NamesList PostgreSqlView::makeListWithNamesFromQuery(
        const QString &connectionName, const QString &queryString,
        const std::function<QString (QSqlRecord)>& fn,
        const std::function<void(void)>& onError)
{
    auto connect = QSqlDatabase::database(connectionName);

    QSqlQuery query(connect);
    if ( !query.exec(queryString) ) {
        onError();
    }

    NamesList resultList;
    while ( query.next() ) {
        QSqlRecord record = query.record();
        resultList.push_back(fn(record));
    }

    return resultList;
}

void PostgreSqlView::disconnectFromDatabase(const QString &connectionName)
{
    QSqlDatabase::removeDatabase(connectionName);
}
