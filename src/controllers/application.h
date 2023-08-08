#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>

#define APP() Application::instance()

class Application : public QObject
{
    Q_OBJECT
public:
    static Application &instance();

    explicit Application(QQmlApplicationEngine &engine, QObject *parent = nullptr);

signals:

private:
    static Application *sm_instance;

    QQmlApplicationEngine &m_qml_engine;
};

#endif // APPLICATION_H
