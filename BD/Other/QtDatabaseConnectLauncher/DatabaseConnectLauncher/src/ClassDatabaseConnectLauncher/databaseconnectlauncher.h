#ifndef DATABASECONNECTLAUNCHER_H
#define DATABASECONNECTLAUNCHER_H

#include <QDialog>

class QLineEdit;
class QGroupBox;

class DatabaseConnectLauncher : public QDialog
{
    Q_OBJECT

private:
    QString _defaultUserName = "";
    QString _defaultUserPassword = "";
    QString _defaultServerAddres = "";
    QString _defaultServerPort = "";
    QString _defaultDatabaseName = "";
    bool _needSavePasswordInConnectObject = false;

    QLineEdit* _editUserName = nullptr;
    QLineEdit* _editUserPassword = nullptr;
    QLineEdit* _editServerAddres = nullptr;
    QLineEdit* _editServerPort = nullptr;
    QLineEdit* _editDatabaseName = nullptr;

    QString _databaseConnectName = "";

public:
    explicit DatabaseConnectLauncher(QWidget * parent = nullptr);
    DatabaseConnectLauncher(const DatabaseConnectLauncher &) = delete;
    DatabaseConnectLauncher(const DatabaseConnectLauncher &&) = delete;
    DatabaseConnectLauncher& operator = (const DatabaseConnectLauncher &) = delete;
    DatabaseConnectLauncher& operator = (const DatabaseConnectLauncher &&) = delete;
    ~DatabaseConnectLauncher() override = default;

    QString getConnectName();

    void setMaxUserNameTextLength(quint32 maxLength);
    void setMaxUserPasswordTextLength(quint32 maxLength);
    void setMaxServerAddresTextLength(quint32 maxLength);
    void setMaxDatabaseNameTextLength(quint32 maxLength);

    void setDefaultUserName(const QString& userName);
    void setDefaultUserPassword(const QString& password);
    void setDefaultServerAddres(const QString& addres);
    void setDefaultServerPort(const QString& port);
    void serDefaultDatabaseName(const QString& databaseName);

    void savePasswordOnConnectObject(bool needSave);

    void setStyleSheetFromSrc(const QString& fileName);

public slots:
    int exec() override;

private slots:
    void onTryConnect();

private:
    void setUI();
    void setLineEditHendlers();
    QGroupBox* makeUserInputBox();
    QGroupBox* makeDatabaseInputBox();

    bool validateFields();
    bool tryConnectToDatabase();

};

#endif // DATABASECONNECTLAUNCHER_H
