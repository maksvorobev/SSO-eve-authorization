#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Authorization_engine.h"
#include "Tcp_server.h"
#include <iostream>
#include <QQmlContext>
#include <QSslSocket>
int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    std::string Client_ID = "";
    std::string requirements = "";

    Authorization_engine* A_eng = new Authorization_engine(
        QString::fromStdString(Client_ID),
        QString::fromStdString(requirements)
    );
    Tcp_server* tcp_server = new Tcp_server(A_eng);
    tcp_server->run_Tcp_server();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/eve_authorization/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.rootContext()->setContextObject(A_eng);
    engine.load(url);

    return app.exec();
}
