#ifndef AUTHORIZATION_ENGINE_H
#define AUTHORIZATION_ENGINE_H

#include <QObject>
#include <QUrl>
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QUrlQuery>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QUuid>
#include "Validating_JWT.h"
#include <QSharedPointer>

class Authorization_engine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString p_Direct_URL READ p_Direct_URL CONSTANT)

public:
    explicit Authorization_engine(
        QString Client_ID,
        QString requirements,
        QObject *parent = nullptr
        );
private:
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString Client_ID;
    QUrl Callback_URL = QString("http://localhost:8080/oauth-callback");
    QString requirements;
    QUrl POST_URL = QString("https://login.eveonline.com/v2/oauth/token");
    QByteArray Code_verifier;
    QUrl Direct_URL = QString("https://login.eveonline.com/v2/oauth/authorize/");
    QString percent_encoding(const QString& param);
    QString codeChallenge;
    QString authorization_code;

    QUrl make_authorization_url();
    QNetworkReply* GET_request(const QUrl& url);
    void POST_request_for_token(const QUrl& url);
    QByteArray generateCodeVerifier();
    QByteArray createCodeChallenge(const QByteArray& Code_verifier);

public:
    QString p_Direct_URL();
signals:


public slots:
    void get_code(QString code);
protected slots:
    void get_answer(QNetworkReply *reply);
    void get_POST_RESPONSE_for_token(QNetworkReply *reply);
};

#endif // AUTHORIZATION_ENGINE_H
