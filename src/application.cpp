#include "application.h"

#include <QQmlContext>

#include "models/sentencesmodel.h"

Application *Application::sm_instance = nullptr;

Application &Application::instance()
{
    Q_ASSERT(sm_instance != nullptr);
    return *sm_instance;
}

Application::Application(QQmlApplicationEngine &engine, QObject *parent) :
    QObject(parent), m_qml_engine(engine), m_document(new Document(this))
{
    Q_ASSERT(sm_instance == nullptr);
    sm_instance = this;
}

void Application::init()
{
    m_qml_engine.rootContext()->setContextProperty(QStringLiteral("app"), this);

    qmlRegisterType<SentencesModel>("speechwriter", 1, 0, "SentencesModel");
}

Document &Application::document()
{
    return *m_document;
}
