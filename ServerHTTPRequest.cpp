#include "ServerHTTPRequest.h"


#define DEBUG_FLAG false
/*
  Creates a new ServerHTTPRequest that will handle
  data coming over the TCP socket

     TCPSocket - The socket over which information
     will be transferred
  */
ServerHTTPRequest::ServerHTTPRequest(QTcpSocket * TCPSocket) : ServerTCPRequest(TCPSocket){

 }

 /*
  Fills the ServerHTTPRequest by extracting the body
  and the url from the HTTP request.

         httpBody - Output parameter to hold the
         data that came in the body of the HTTP
         request.

         url - Output parameter to hold the url
         of the request
   */
 int ServerHTTPRequest::fillHTTPRequest(QString& httpBody, QString& url){

     int result = 0;
     QString * data = NULL;

     do{
         result = fillTCPRequest();
         data = getTCPData();
         if(result!=0){
             qDebug() << "CONNECTION WITH CLIENT LOST";
             return result;
         }
         qDebug() << "TRYING TO CONSTRUCT HTTP REQUEST";
     }while(constructHTTPRequestFromData(httpBody, url, data) != 0);
      qDebug() << "HTTP REQUEST CONSTRUCTED";
     return 0;

 }

 int ServerHTTPRequest::constructHTTPRequestFromData(QString& body, QString &url, const QString * d){

     QString data(*d); // Lets make a local copy instead of using the arrow operator

     QStringList headerBody = data.split(QString("\r\n\r\n"));

     if(headerBody.length() < 2){ // We must at least have a header and a body
         return 1;
     }

     QString header = headerBody.at(0);

     QStringList headerFields = header.split(QString("\r\n"));

     if(headerFields.length() < 2){ // We must at least have the protocol, and the content length
         return 1;
     }

     QString protocolLine = headerFields.at(0);

     QStringList protocolLineElements = protocolLine.split(" ");

     if(protocolLineElements.length() < 3){ // We must have at least the type, url and protocol
         return 1;
     }

     QString httpType = protocolLineElements.at(0);

     QString httpUrl = protocolLineElements.at(1);

     QString httpProtocol = protocolLineElements.at(2);

     QString contentLengthLine = headerFields.at(1);



     contentLengthLine.replace(QString("Content-Length: "), "");

     int contentLength = contentLengthLine.toInt();
     if(DEBUG_FLAG){
        qDebug() << contentLength;
        qDebug() << header.length();
        qDebug() <<data.length();
     }
     if(contentLength + header.length() + 4 != data.length()){ // We need to have all of the body data before proceeding
         return 1;
     }

     QString bodyData = data.right(contentLength);

     body = bodyData;

     url = httpUrl;

     if(DEBUG_FLAG){
        qDebug() << "DATA: " << data;
        qDebug() << "BODY: " << body << "";
        qDebug() << "URL: " << url << "";
     }

     return 0;

 }

 // Destructor
 ServerHTTPRequest::~ServerHTTPRequest(){

 }
