/*

  By: Spencer Whyte
  # 100817664
  Carleton University
  */

/*
#include "XMLRequest.h"

XMLRequest::XMLRequest(QString &d):document(NULL), database(NULL)
{
    qDebug() << "DATA RECEIVED: "<< d;
    QDomDocument * doc = new QDomDocument("Login Request");
    doc->setContent(d);
    setDocument(doc);

}

CUCareDatabase * XMLRequest::getDatabase(){
    return database;
}

void XMLRequest::setDatabase(CUCareDatabase * d){
    if(database){
        delete database;
    }
    database = d;
}

QString * XMLRequest::getResponse(){
    return new QString("FAILURE, SOMEONE FORGOT TO IMPLEMENT GET RESPONSE IN THE SUBCLASS");
}

QDomDocument * XMLRequest::getDocument(){
    return document;
}

void XMLRequest::setDocument(QDomDocument * d){
    if(document){
        delete document;
    }
    document = d;
}

XMLRequest::~XMLRequest(){
    delete document;
}

*/
