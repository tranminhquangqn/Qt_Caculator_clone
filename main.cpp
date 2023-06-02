#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "standard.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Standard standard;
    engine.rootContext()->setContextProperty("standard", &standard);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
