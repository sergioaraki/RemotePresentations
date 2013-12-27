#include "Request.hpp"

Request::Request(QObject* parent)
    : QObject(parent)
    , m_networkAccessManager(new QNetworkAccessManager(this))
{
}


void Request::getRequest(QString url)
{
    const QUrl q_url(url);

    QNetworkRequest request(q_url);

    QNetworkReply* reply = m_networkAccessManager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onGetReply()));
}

void Request::onGetReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QVariant response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();

            if (available > 0) {

                const QByteArray buffer(reply->readAll());

				response = buffer;
            }

        } else {
        	qDebug() <<  tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
            response = 0;
        }

        reply->deleteLater();
    }

    emit complete(response);
}
