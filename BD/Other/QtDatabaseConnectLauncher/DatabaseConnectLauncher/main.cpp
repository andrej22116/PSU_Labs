#include "databaseconnectlauncher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseConnectLauncher w;
    w.show();

    return a.exec();
}
