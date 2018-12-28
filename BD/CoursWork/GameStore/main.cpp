#include "mainwindow.h"
#include <QApplication>

#include <QMessageBox>

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include "code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h"
#include <QDebug>

void initializeDatabaseConnection();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if ( !DatabaseBaseController::connect() ) {
        QMessageBox msg{};
        msg.setWindowTitle("Error!");
        msg.setText(DatabaseBaseController::getLastError());
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }


    MainWindow w;
    w.show();

    return a.exec();
}
