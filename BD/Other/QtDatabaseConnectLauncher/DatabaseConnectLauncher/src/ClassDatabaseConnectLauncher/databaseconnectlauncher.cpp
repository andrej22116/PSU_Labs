#include "databaseconnectlauncher.h"

#include <QIntValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QStyle>
#include <QGroupBox>

#include <QFile>

DatabaseConnectLauncher::DatabaseConnectLauncher(QWidget *parent) :
    QDialog(parent),
    _editUserName(new QLineEdit()),
    _editUserPassword(new QLineEdit()),
    _editServerAddres(new QLineEdit()),
    _editServerPort(new QLineEdit()),
    _editDatabaseName(new QLineEdit())
{
    this->setObjectName("dialog");
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |
                         Qt::CustomizeWindowHint |
                         Qt::WindowCloseButtonHint);
    setUI();
    setLineEditHendlers();
}

QString DatabaseConnectLauncher::getConnectName()
{
    return _databaseConnectName;
}

void DatabaseConnectLauncher::setUI()
{
    _editServerPort->setMaxLength(5);
    _editServerPort->setValidator(new QIntValidator(0, 65535, _editServerPort));

    auto dialogLayout = new QGridLayout(this);
    dialogLayout->setColumnStretch(0, 1);
    dialogLayout->setColumnStretch(2, 1);
    dialogLayout->setRowStretch(0, 1);
    dialogLayout->setRowStretch(5, 1);

    auto buttonLogin = new QPushButton("Подключиться");
    auto buttonCancel = new QPushButton("Отмена");

    dialogLayout->addWidget(makeUserInputBox(), 1, 1);
    dialogLayout->addWidget(makeDatabaseInputBox(), 2, 1);
    dialogLayout->addWidget(buttonLogin, 3, 1);
    dialogLayout->addWidget(buttonCancel, 4, 1);
}

void DatabaseConnectLauncher::setLineEditHendlers()
{
    _editUserName->setProperty("error", true);
    _editUserPassword->setProperty("error", true);
    _editServerAddres->setProperty("error", true);
    _editServerPort->setProperty("error", true);
    _editDatabaseName->setProperty("error", true);

    auto setLineEditProperty = [](QLineEdit* lineEdit, const QString& newText) {
        bool isError = lineEdit->property("error").toBool();
        int textLength = newText.length();

        bool needUpdate = false;
        if (textLength == 0 && !isError) {
            lineEdit->setProperty("error", true);
            needUpdate = true;
        }
        else if (textLength > 0 && isError) {
            lineEdit->setProperty("error", false);
            needUpdate = true;
        }

        if (needUpdate) {
            lineEdit->style()->unpolish(lineEdit);
            lineEdit->style()->polish(lineEdit);
        }
    };

    connect(_editUserName, &QLineEdit::textChanged, this, [=](const QString& newText){
        setLineEditProperty(_editUserName, newText);
    });
    connect(_editUserPassword, &QLineEdit::textChanged, this, [=](const QString& newText){
        setLineEditProperty(_editUserPassword, newText);
    });
    connect(_editServerAddres, &QLineEdit::textChanged, this, [=](const QString& newText){
        setLineEditProperty(_editServerAddres, newText);
    });
    connect(_editServerPort, &QLineEdit::textChanged, this, [=](const QString& newText){
        setLineEditProperty(_editServerPort, newText);
    });
    connect(_editDatabaseName, &QLineEdit::textChanged, this, [=](const QString& newText){
        setLineEditProperty(_editDatabaseName, newText);
    });
}

QGroupBox* DatabaseConnectLauncher::makeUserInputBox()
{
    auto userBox = new QGroupBox("Пользователь");
    auto layout = new QGridLayout(userBox);

    layout->addWidget(_editUserName);
    layout->addWidget(_editUserPassword);
    _editUserName->setPlaceholderText("Логин");
    _editUserPassword->setPlaceholderText("Пароль");

    _editUserName->setObjectName("loginField");
    _editUserPassword->setObjectName("passwordField");
    userBox->setObjectName("userGroupBox");

    return userBox;
}

QGroupBox* DatabaseConnectLauncher::makeDatabaseInputBox()
{
    auto databaseBox = new QGroupBox("База данных");
    auto layout = new QGridLayout(databaseBox);

    layout->addWidget(_editServerAddres, 0, 0);
    layout->addWidget(_editServerPort, 0, 1);
    layout->addWidget(_editDatabaseName, 1, 0, 1, 2);
    _editServerAddres->setPlaceholderText("Адрес сервера");
    _editServerPort->setPlaceholderText("Порт");
    _editDatabaseName->setPlaceholderText("Название базы данных");

    _editServerAddres->setObjectName("serverAddresField");
    _editServerPort->setObjectName("serverPortField");
    _editDatabaseName->setObjectName("databaseNameField");
    databaseBox->setObjectName("databaseGroupBox");

    return databaseBox;
}

void DatabaseConnectLauncher::setMaxUserNameTextLength(quint32 maxLength)
{
    if ( maxLength == 0 ) { return; }

    _editUserName->setMaxLength(maxLength);
    _editUserName->setText(_editUserName->text().left(maxLength));
}

void DatabaseConnectLauncher::setMaxUserPasswordTextLength(quint32 maxLength)
{
    if ( maxLength == 0 ) { return; }

    _editUserPassword->setMaxLength(maxLength);
    _editUserPassword->setText(_editUserPassword->text().left(maxLength));
}

void DatabaseConnectLauncher::setMaxServerAddresTextLength(quint32 maxLength)
{
    if ( maxLength == 0 ) { return; }

    _editServerAddres->setMaxLength(maxLength);
    _editServerAddres->setText(_editServerAddres->text().left(maxLength));
}

void DatabaseConnectLauncher::setMaxDatabaseNameTextLength(quint32 maxLength)
{
    if ( maxLength == 0 ) { return; }

    _editDatabaseName->setMaxLength(maxLength);
    _editDatabaseName->setText(_editDatabaseName->text().left(maxLength));
}


void DatabaseConnectLauncher::setDefaultUserName(const QString& userName)
{
    _defaultUserName = userName.left(_editUserName->maxLength());
}

void DatabaseConnectLauncher::setDefaultUserPassword(const QString& password)
{
    _defaultUserPassword = password.left(_editUserPassword->maxLength());
}

void DatabaseConnectLauncher::setDefaultServerAddres(const QString& addres)
{
    _defaultServerAddres = addres.left(_editServerAddres->maxLength());
}

void DatabaseConnectLauncher::setDefaultServerPort(const QString& port)
{
    _defaultServerPort = port.left(_editServerPort->maxLength());
}

void DatabaseConnectLauncher::serDefaultDatabaseName(const QString& databaseName)
{
    _defaultDatabaseName = databaseName.left(_editDatabaseName->maxLength());
}


void DatabaseConnectLauncher::savePasswordOnConnectObject(bool needSave)
{
    _needSavePasswordInConnectObject = needSave;
}


void DatabaseConnectLauncher::setStyleSheetFromSrc(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::OpenModeFlag::ReadOnly)) {
        return;
    }

    this->setStyleSheet(QString(file.readAll()));

    file.close();

    this->setFixedSize(this->layout()->sizeHint());
}

int DatabaseConnectLauncher::exec()
{
    _editUserName->setText(_defaultUserName);
    _editUserPassword->setText(_defaultUserPassword);
    _editServerAddres->setText(_defaultServerAddres);
    _editServerPort->setText(_defaultServerPort);
    _editDatabaseName->setText(_defaultDatabaseName);

    return QDialog::exec();
}

void DatabaseConnectLauncher::onTryConnect()
{

}

bool DatabaseConnectLauncher::validateFields()
{
    return true;
}

bool DatabaseConnectLauncher::tryConnectToDatabase()
{
    return true;
}
