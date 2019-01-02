#include "mainwindow.h"
#include <QApplication>

#include <QMessageBox>

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include "code/control/ClassGameDatabaseController/gamedatabasecontroller.h"
#include "code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h"
#include <QCoreApplication>

void initializeDatabaseConnection();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::addLibraryPath("./");
    QCoreApplication::setOrganizationName("15-IT-1");
    QCoreApplication::setOrganizationDomain("15-it-1.psu");
    QCoreApplication::setApplicationName("GameStore");

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
