#ifndef POSTGRESQLVIEW_H
#define POSTGRESQLVIEW_H

#include <QVector>
#include <QMap>
#include <exception>

using NamesList = QVector<QString>;
using DbList = NamesList;
using SchemasList = NamesList;
using TablesList = NamesList;
using ColumnsList = NamesList;
using FunctionsList = NamesList;
using FunctionParametersList = NamesList;

class PostgreSqlView
{    
private:
    QString serverUrl_;
    int serverPort_ = 5432;
    QString dbName_;
    QString userLogin_;
    QString userPassword_;

public:
    PostgreSqlView() = default;

    PostgreSqlView( const PostgreSqlView& pgSqlView ) noexcept;
    PostgreSqlView( PostgreSqlView&& pgSqlView ) = delete;

    PostgreSqlView& operator = ( const PostgreSqlView& pgSqlView ) = default;
    PostgreSqlView& operator = ( PostgreSqlView&& pgSqlView ) = delete;

    ~PostgreSqlView() = default;


    /*!
     * \brief setConnectInfo to PG server to DB with name "DB"
     * with login "postgres"
     *
     * \param databaseUrl - PostgreSQL server address
     * \param databasePort - PostgreSQL server port
     * \param password - password for user "postgres"
     */
    void setConnectInfo( const QString& databaseUrl
                       , int databasePort
                       , const QString& password
                       ) noexcept;


    /*!
     * \brief setConnectInfo to PG server to DB with name "DB" with user login
     * using user "login" and "password"
     *
     * \param databaseUrl - PostgreSQL server address
     * \param databasePort - PostgreSQL server port
     * \param login - user login for connect to DB "postgres"
     * \param password - password for user login
     */
    void setConnectInfo( const QString& databaseUrl
                       , int databasePort
                       , const QString& login
                       , const QString& password
                       ) noexcept;


    /*!
     * \brief setConnectInfo to PG server to DB with "dbName",
     * using user "login" and "password"
     *
     * \param databaseUrl - PostgreSQL server address
     * \param databasePort - PostgreSQL server port
     * \param dbName - database name
     * \param login - user login for connect to DB
     * \param password - password for user login
     */
    void setConnectInfo( const QString& databaseUrl
                       , int databasePort
                       , const QString& dbName
                       , const QString& login
                       , const QString& password
                       ) noexcept;


    /*!
     * \brief getDatabasesList
     * \return list of database names
     */
    DbList getDatabasesList() noexcept(false);


    /*!
     * \brief getDatabaseSchemasList
     * \param databaseName
     * \return all schema names in database
     */
    SchemasList getDatabaseSchemasList
                    ( const QString& databaseName
                    ) noexcept(false);


    /*!
     * \brief getDatabaseSchemaTablesList
     * \param databaseName
     * \param schemaName
     * \return all table names in database schema
     */
    TablesList getDatabaseSchemaTablesList
                    ( const QString& databaseName
                    , const QString& schemaName
                    ) noexcept(false);


    /*!
     * \brief getDatavaseSchemaTableColumnsList
     * \param databaseName
     * \param schemaName
     * \param tableName
     * \return all column names in database schema table
     */
    ColumnsList getDatavaseSchemaTableColumnsList
                    ( const QString& databaseName
                    , const QString& schemaName
                    , const QString& tableName
                    ) noexcept(false);


    /*!
     * \brief getDatabaseFunctionsList
     * \param databaseName
     * \param schemaName
     * \return all function names in database schema
     */
    FunctionsList getDatabaseFunctionsList
                    ( const QString& databaseName
                    , const QString& schemaName
                    ) noexcept(false);


    /*!
     * \brief getDatabaseFunctionParametersList
     * \param databaseName
     * \param schemaName
     * \return all function parametr names in database schema
     */
    FunctionParametersList getDatabaseFunctionParametersList
                    ( const QString& databaseName
                    , const QString& schemaName
                    , const QString& functionName
                    ) noexcept(false);


private:
    QString getDatabaseConnectionName(const QString& databaseName) noexcept(false);

    void disconnectFromDatabase(const QString& connectionName) noexcept(false);
};

#endif // POSTGRESQLVIEW_H
