#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/ClassConnectionToDbController/connectontodbcontroller.h"

void registerTypesForQml();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    registerTypesForQml();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

void registerTypesForQml()
{
    qmlRegisterType<ConnectonToDbController>("Database.Controls", 1, 0, "DbConnectionDialog");
}
