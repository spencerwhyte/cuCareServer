#ifndef XMLREQUEST_H
#define XMLREQUEST_H

#include <QObject>
#include <QDebug>
#include <QtXml>
#include "CUCareDatabase.h"

class XMLRequest : public QObject
{
    Q_OBJECT
    void setDocument(QDomDocument * document);
    CUCareDatabase * database;
public:
    XMLRequest(QString &data);
    QDomDocument * document;
    QDomDocument * getDocument();
    virtual QString * getResponse();

    CUCareDatabase * getDatabase();
    void setDatabase(CUCareDatabase * d);

    ~XMLRequest();
signals:
    
public slots:
    
};

#endif // XMLREQUEST_H
