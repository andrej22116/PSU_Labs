#ifndef DATABASECONNECTDIALOG_H
#define DATABASECONNECTDIALOG_H

#include <QDialog>
#include <QtSql>

class QLineEdit;

class DataBaseConnectDialog : public QDialog
{
    QLineEdit* editDatabaseName = nullptr;
    QLineEdit* editAddres = nullptr;
    QLineEdit* editPort = nullptr;
    QLineEdit* editLogin = nullptr;
    QLineEdit* editPassword = nullptr;

    QSqlDatabase database;

public:
    DataBaseConnectDialog(QWidget* parent = nullptr);

    QSqlDatabase getDatabaseConnect() { return database; };

private slots:
    bool tryConnect();
};

#endif // DATABASECONNECTDIALOG_H
