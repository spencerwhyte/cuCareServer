#include "HTTPResponse.h"


HTTPResponse::HTTPResponse(QString * b) : body(NULL)
{
    setBody(b);
}

QString * HTTPResponse::getBody(){
    return body;
}

void HTTPResponse::setBody(QString * b){
    if(body){
        delete body;
    }
    body = b;
}

QByteArray * HTTPResponse::getResponseData(){
    QByteArray * header =new QByteArray();
    QByteArray * bodyArray =new QByteArray();

    header->append("HTTP/1.1 200 OK\n");
    header->append(QString("Content-Length: ")).append(QString().setNum(getBody()->length()));
    header->append("\n");
    header->append("\r\n");


    bodyArray->append(*getBody());

    header->append(*bodyArray);
    delete bodyArray;
    qDebug() << "BODY: " << *header ;
    return header;
}
