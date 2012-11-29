#include "ServerHTTPRequest.h"

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

     int result = fillTCPRequest();
     QString * data = getTCPData();

     while(constructHTTPRequestFromData(httpBody, url, data) != 0){
         if(result!=0){
             return result;
         }
         result = fillTCPRequest();
         data = getTCPData();
     }

     return 0;

 }

 int ServerHTTPRequest::constructHTTPRequestFromData(QString& body, QString &url, const QString * d){

     QString data(*d); // Lets make a local copy instead of using the arrow operator

     QStringList headerBody = data.split(QString("\r\n"));

     if(headerBody.length() < 2){ // We must at least have a header and a body
         return 1;
     }

     QString header = headerBody.at(0);

     QStringList headerFields = header.split(QString("\n"));

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

     QStringList contentLengthPossibilities = contentLengthLine.split(QString("Content-Length: "));

     if(contentLengthPossibilities.length() < 1){ // We need to have a content length before proceeding
         return 1;
     }

     int contentLength = contentLengthPossibilities.at(0).toInt();

     if(contentLength + header.length() + 2 == data.length()){ // We need to have all of the body data before proceeding
         return 1;
     }

     QString bodyData = data.right(contentLength);

     body = bodyData;

     url = httpUrl;

     return 0;

 }

 // Destructor
 ServerHTTPRequest::~ServerHTTPRequest(){

 }
