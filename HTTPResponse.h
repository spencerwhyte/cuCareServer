#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QByteArray>


class HTTPResponse
{

    QString * body;

public:
    HTTPResponse(QString * xmlData);

    QString * getBody();

    void setBody(QString * b);

    QByteArray * getResponseData();
};

#endif // HTTPRESPONSE_H
