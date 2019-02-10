#include "MainWindow.hpp"
#include <QApplication>

#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    qDebug() << QDir::currentPath();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
