#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "controllers/document.h"

#define APP() Application::instance()

class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Document *document MEMBER m_document CONSTANT)

public:
    static Application &instance();

    explicit Application(QQmlApplicationEngine &engine, QObject *parent = nullptr);

    void init();

    Document &document();

private:
    static Application *sm_instance;

    QQmlApplicationEngine &m_qml_engine;
    Document *m_document;
};

#endif // APPLICATION_H
