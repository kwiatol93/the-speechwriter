#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "controllers/application.h"

int main(int argc, char *argv[])
{
    QGuiApplication gui(argc, argv);
    QQmlApplicationEngine engine;
    Application app(engine, &gui);

    const QUrl url(u"qrc:/speechwriter/qml/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &gui,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return gui.exec();
}
