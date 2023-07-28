#include "Tcp_server.h"

Tcp_server::Tcp_server(Authorization_engine* A_eng, QObject *parent):
    A_eng(A_eng),
    QTcpServer(parent)
{

}

void Tcp_server::run_Tcp_server()
{
    if (listen(QHostAddress::Any, 8080)){
        return;
    }
    else {
        // TODO
        throw std::runtime_error("server dosen't run");
        return;
    }
}

QString Tcp_server::getCode() const
{
    return code;
}

void Tcp_server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Tcp_server::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &Tcp_server::sockDisc);

    return;
}

void Tcp_server::sockReady()
{
    auto ans_string = QString::fromStdString(socket->readAll().toStdString());
    QString queryString = QUrl(ans_string).query();
    QUrlQuery query(queryString);
    code = query.queryItemValue("code");

    connect(this, &Tcp_server::sent_code, A_eng, &Authorization_engine::get_code);
    emit sent_code(code);
    return;
}

void Tcp_server::sockDisc()
{
    socket->deleteLater();
    return;
}
