#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <stdexcept>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QUrl>
#include <QUrlQuery>
#include "Authorization_engine.h"

class Tcp_server: public QTcpServer
{
    Q_OBJECT
public:
    Tcp_server(Authorization_engine* A_eng, QObject *parent = nullptr);
    void run_Tcp_server();

    QString getCode() const;

private:
    Authorization_engine* A_eng;
    QTcpSocket* socket;
    QByteArray Data;
    QString code;
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void sent_code(QString code);
public slots:
    void sockReady();
    void sockDisc();
};

#endif // TCP_SERVER_H
