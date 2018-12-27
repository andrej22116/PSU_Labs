#include "mainwindow.h"
#include <QApplication>

#include <QMessageBox>

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include <QDebug>

void initializeDatabaseConnection();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if ( !DatabaseBaseController::connect() ) {
        QMessageBox msg{};
        msg.setWindowTitle("Error!");
        msg.setText(DatabaseBaseController::getLastError());
        msg.setIcon(QMessageBox::Critical);
        msg.setParent(&w);
        msg.exec();
    }

    try {
        CurrentUser user;
        user.token = "479b0b9ee6e7366c9f29e3ad2057c0bfd6abd5de";
        for (auto& game : GameDatabaseController::getUserGameNameList(user)) {
            qDebug() << game;
        }
    }
    catch (QString& errMsg) {
        QMessageBox msg{};
        msg.setWindowTitle("Error!");
        msg.setText(errMsg);
        msg.setIcon(QMessageBox::Critical);
        msg.setParent(&w);
        msg.exec();
    }


    return a.exec();
}
