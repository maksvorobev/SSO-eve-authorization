#ifndef VALIDATING_JWT_H
#define VALIDATING_JWT_H
#include <QString>
#include <string>
#include <iostream>
#include <QByteArray>
#include <QDebug>
#include <sstream>
#include "./third-party-lib/jwt-cpp/jwt-cpp/jwt.h"
#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

class Validating_JWT: public QObject
{
    Q_OBJECT
public:
    Validating_JWT(QNetworkAccessManager *manager, QString access_token);
private:
    QString access_token;
    void extract_nn_and_ee(const QByteArray& answer);
    void final_check(const QString& ee, const QString& nn);
    QUrl SSO_key_storage = QUrl("https://login.eveonline.com/oauth/jwks");
    QNetworkAccessManager *manager;
    void send_GET_request_to_SSO_key_storage();
    QString ConvertJwkToPem_V2(const QString& nn, const QString& ee);
    bool veri_jwt_token(QString strToken, QString rsa_pub_key);

protected slots:
    void get_responce_from_SSO_key_storage(QNetworkReply *reply);

};

#endif // VALIDATING_JWT_H
