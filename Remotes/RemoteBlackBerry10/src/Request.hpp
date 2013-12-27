#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <QtCore/QObject>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>

class QNetworkAccessManager;

class Request : public QObject
{
    Q_OBJECT
public:
    Request(QObject* parent = 0);

public Q_SLOTS:
    void getRequest(QString url);

Q_SIGNALS:
    void complete(const QVariant &info);

private Q_SLOTS:
    void onGetReply();

private:
    QNetworkAccessManager* m_networkAccessManager;
};

#endif
