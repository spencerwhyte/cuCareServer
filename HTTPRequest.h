#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QStringList>
#include <QTcpSocket>
#include <QUrl>
#include <LoginRequest.h>
#include "HTTPResponse.h"

class HTTPRequest : public QObject
{
    Q_OBJECT

    typedef enum HTTPRequestOperation{
        POST, GET, INVALID
    }HTTPRequestOperation;

    QStringList * header;

    void setHeader(QStringList * header );

public:
    explicit HTTPRequest(QTcpSocket &socket);
    
    QStringList* getHeader();

    HTTPRequest::HTTPRequestOperation getOperation();

    QString * getPath();

    bool isHTTPProtocol();

    long getContentLength();

    ~HTTPRequest();

signals:
    
public slots:
    
};

#endif // HTTPREQUEST_H
