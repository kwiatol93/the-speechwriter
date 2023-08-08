#include "application.h"

#include <QQmlContext>

Application *Application::sm_instance = nullptr;

Application &Application::instance()
{
    Q_ASSERT(sm_instance != nullptr);
    return *sm_instance;
}

Application::Application(QQmlApplicationEngine &engine, QObject *parent) :
    QObject(parent), m_qml_engine(engine)
{
    Q_ASSERT(sm_instance == nullptr);
    sm_instance = this;

    m_qml_engine.rootContext()->setContextProperty(QStringLiteral("app"), this);
}
