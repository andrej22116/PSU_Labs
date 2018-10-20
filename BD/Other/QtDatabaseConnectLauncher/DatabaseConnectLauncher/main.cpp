#include "src/ClassDatabaseConnectLauncher/databaseconnectlauncher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseConnectLauncher w;
    w.setStyleSheetFromSrc(":/style/base.qss");
    w.show();

    return a.exec();
}
