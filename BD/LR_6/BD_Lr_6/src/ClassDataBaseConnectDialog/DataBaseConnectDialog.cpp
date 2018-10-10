#include "DataBaseConnectDialog.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>

DataBaseConnectDialog::DataBaseConnectDialog(QWidget* parent) : QDialog(parent)
{
    this->setWindowTitle("Подключение к базе данных");

    auto layout = new QGridLayout(this);

    editDatabaseName = new QLineEdit("BD_Labs");
    editAddres = new QLineEdit("127.0.0.1");
    editPort = new QLineEdit("5432");
    editLogin = new QLineEdit("postgres");
    editPassword = new QLineEdit("andrej22116");

    editPassword->setEchoMode(QLineEdit::EchoMode::Password);

    auto connect = new QPushButton("Подключиться");
    auto cancel = new QPushButton("Отмена");

    layout->addWidget(new QLabel("Адрес:"), 0, 0);
    layout->addWidget(editDatabaseName, 0, 1);

    layout->addWidget(new QLabel("Адрес:"), 1, 0);
    layout->addWidget(editAddres, 1, 1);

    layout->addWidget(new QLabel("Порт:"), 2, 0);
    layout->addWidget(editPort, 2, 1);

    layout->addWidget(new QLabel("Логин:"), 3, 0);
    layout->addWidget(editLogin, 3, 1);

    layout->addWidget(new QLabel("Пароль:"), 4, 0);
    layout->addWidget(editPassword, 4, 1);

    layout->addWidget(connect, 5, 0);
    layout->addWidget(cancel, 5, 1);

    DataBaseConnectDialog::connect(connect, &QPushButton::clicked, this, &DataBaseConnectDialog::tryConnect);
    DataBaseConnectDialog::connect(cancel, &QPushButton::clicked, this, &DataBaseConnectDialog::reject);
}

bool DataBaseConnectDialog::tryConnect()
{
    database = QSqlDatabase::addDatabase("QPSQL", editDatabaseName->text());
    database.setDatabaseName(editDatabaseName->text());

    database.setHostName(editAddres->text());
    database.setPort(editPort->text().toInt());

    database.setUserName(editLogin->text());
    database.setPassword(editPassword->text());

    if (!database.open()) {
        QSqlDatabase::removeDatabase(editDatabaseName->text());
        database.close();
        QMessageBox msg("Ошибка", "Не удалось подключиться к базе данных!",
                        QMessageBox::Icon::Critical,
                        QMessageBox::Button::Ok,
                        QMessageBox::Button::NoButton,
                        QMessageBox::Button::NoButton,
                        this);
        msg.exec();
    } else {
        this->close();
    }
}
