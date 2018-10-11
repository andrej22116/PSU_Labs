#ifndef DATABASECONNECTLAUNCHER_H
#define DATABASECONNECTLAUNCHER_H

#include <QDialog>

class QLineEdit;

class DatabaseConnectLauncher : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* editUserName;
    QLineEdit* editUserPassword;
    QLineEdit* editServerAddres;
    QLineEdit* editServerPort;
    QLineEdit* editDatabaseName;

    QString _databaseConnectName;

public:
    explicit DatabaseConnectLauncher(QWidget * parent = nullptr);
    DatabaseConnectLauncher(const DatabaseConnectLauncher &) = delete;
    DatabaseConnectLauncher(const DatabaseConnectLauncher &&) = delete;
    DatabaseConnectLauncher& operator = (const DatabaseConnectLauncher &) = delete;
    DatabaseConnectLauncher& operator = (const DatabaseConnectLauncher &&) = delete;
    ~DatabaseConnectLauncher() override;

    QString getConnectName();

    void setMaxUserNameTextLength();
    void setMaxUserPasswordTextLength();
    void setMaxServerAddresTextLength();
    void setMaxDatabaseNameTextLength();

    void setDefaultUserName(QString userName);
    void setDefaultUserPassword(QString password);
    void setDefaultServerAddres(QString addres);
    void setDefaultServerPort(QString port);
    void serDefaultDatabaseName(QString databaseName);

    void savePasswordOnConnectObject(bool needSave);

    void setStyleSheetFromFile(QString fileName);

public slots:
    int exec() override;

private slots:
    void onTryConnect();

private:
    void setUI();
    bool validateFields();
    bool tryConnectToDatabase();

};

#endif // DATABASECONNECTLAUNCHER_H
