#include "databaseconnectlauncher.h"

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

DatabaseConnectLauncher::DatabaseConnectLauncher(QWidget *parent) :
    QDialog(parent),
    editUserName(new QLineEdit()),
    editUserPassword(new QLineEdit()),
    editServerAddres(new QLineEdit()),
    editServerPort(new QLineEdit()),
    editDatabaseName(new QLineEdit())
{
    setUI();
}

DatabaseConnectLauncher::~DatabaseConnectLauncher()
{
}

QString DatabaseConnectLauncher::getConnectName()
{
    return _databaseConnectName;
}

void DatabaseConnectLauncher::setUI()
{

}
