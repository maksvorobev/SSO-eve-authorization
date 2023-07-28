#include "Authorization_engine.h"

enum class RESPONSE{

};


Authorization_engine::Authorization_engine(
    QString Client_ID,
    QString requirements,
    QObject *parent
    )
    : QObject{parent},
    Client_ID(Client_ID),
    requirements(requirements)
{

    Code_verifier = generateCodeVerifier();
    //qDebug() << "Code_verifier = " << Code_verifier;
    codeChallenge = QString(createCodeChallenge(Code_verifier));
}

QString Authorization_engine::percent_encoding(const QString& param)
{

    return QString::fromStdString(QUrl::toPercentEncoding(param).toStdString());
}

QUrl Authorization_engine::make_authorization_url()
{

    QUrlQuery q;
    q.addQueryItem(percent_encoding("response_type"), percent_encoding("code"));
    q.addQueryItem(percent_encoding("redirect_uri"), percent_encoding(Callback_URL.toString()));
    q.addQueryItem(percent_encoding("client_id"), percent_encoding(Client_ID));

    q.addQueryItem(percent_encoding("scope"), percent_encoding(requirements));
    q.addQueryItem(percent_encoding("code_challenge"), percent_encoding(codeChallenge));
    q.addQueryItem(percent_encoding("code_challenge_method"), percent_encoding("S256"));
    q.addQueryItem(percent_encoding("state"), percent_encoding(QUuid::createUuid().toString()));
    Direct_URL.setQuery(q);
    return Direct_URL;
}

QNetworkReply* Authorization_engine::GET_request(const QUrl& url)
{
    QNetworkRequest req;
    req.setUrl(url);
    return manager->get(req);
}


void Authorization_engine::POST_request_for_token(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Host", "login.eveonline.com");

    connect(manager,&QNetworkAccessManager::finished,this,&Authorization_engine::get_POST_RESPONSE_for_token);

    QByteArray postData; // payload
    postData.append("grant_type=authorization_code");
    postData.append("&code=" + authorization_code.toUtf8());
    postData.append("&client_id=" + Client_ID.toUtf8());
    postData.append("&code_verifier=" + QByteArray(Code_verifier.constData()));

    QNetworkReply *reply = manager->post(request, postData);

    return;
}

QByteArray Authorization_engine::generateCodeVerifier()
{
    // Generate 32 random bites
    QByteArray randomBytes(32, Qt::Uninitialized);
    for (int i = 0; i < randomBytes.size(); ++i) {
        randomBytes[i] = static_cast<quint8>(QRandomGenerator::global()->generate());
    }
    return randomBytes.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QByteArray Authorization_engine::createCodeChallenge(const QByteArray &Code_verifier)
{
    // Hashing the code identifier using SHA-256
    QByteArray hash = QCryptographicHash::hash(Code_verifier, QCryptographicHash::Sha256);

    return hash.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QString Authorization_engine::p_Direct_URL()
{
    return make_authorization_url().toString();
}



void Authorization_engine::get_answer(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        qDebug() << reply->error();
        return ;
    }
    auto ans = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(ans);
    qDebug() << doc;

    return;



}

void Authorization_engine::get_code(QString code)
{
        authorization_code = code;
        POST_request_for_token(POST_URL);
        return;

}

void Authorization_engine::get_POST_RESPONSE_for_token(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        qDebug() << reply->error();
        reply->deleteLater();
        return ;
    }
    auto ans = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(ans);
    qDebug() << "below your  JSON payload";
    qDebug() << "access_token: "+ doc["access_token"].toString();
    qDebug() << "access_token: " << doc["expires_in"].toDouble();
    qDebug() << "token_type: " + doc["token_type"].toString();
    qDebug() << "refresh_token: " + doc["refresh_token"].toString();
    qDebug() << "";
    qDebug() << "";
    disconnect(manager,&QNetworkAccessManager::finished,this,&Authorization_engine::get_POST_RESPONSE_for_token);


    Validating_JWT* validating_JWT= new Validating_JWT(manager, doc["access_token"].toString());

    /*
    QNetworkAccessManager* manager2 = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://esi.evetech.net/latest/characters/id/wallet/"));
    request.setRawHeader("Authorization", (QString("Bearer ") + doc["access_token"].toString()).toUtf8());

    QNetworkReply* replyy = manager2->get(request);
    QObject::connect(manager2, &QNetworkAccessManager::finished, [](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "OJOJI;" << responseData;
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
    });
    */

    reply->deleteLater();
    return;

}


