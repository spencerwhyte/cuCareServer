#include "ServerObjectResponse.h"

/*
  Creates a new TCPResponse object with the TCP Socket
  over which the data of the response will be sent
  */
ServerObjectResponse::ServerObjectResponse(QTcpSocket * TCPSocket, CUCareDatabase * db) : ServerXMLResponse(TCPSocket) , database(db){

}

/*
  Performs whatever has been requested in the request
  and returns the result of the request to the client
  over the tcp socket

        requestObject - The request being made that should be filled

        type - The type of request to be filled
*/
int ServerObjectResponse::fillObjectResponse(StorableInterface& requestObject, ServerObjectRequest::ObjectRequestType type){

   if(type == ServerObjectRequest::Query || type == ServerObjectRequest::EqualityQuery){
        QList<QMap<QString, QVariant> > responseData;

        bool equality = (type == ServerObjectRequest::EqualityQuery);
        int result = database->queryForObjects(requestObject, responseData, equality);
        QString className = requestObject.className();
        fillXMLResponse(responseData, className);

        return result;

   }else{
       int result;


       if(type == ServerObjectRequest::Add){
            result = database->addObject(requestObject);
       }else if(type == ServerObjectRequest::Edit){
            result = database->editObject(requestObject);
       }else if(type == ServerObjectRequest::Remove){
            result = database->removeObject(requestObject);
       }

       QList<QMap<QString, QVariant> > responseData;
       QMap<QString, QVariant> data;
       requestObject.getAttributesAndValues(data);
       qDebug() << "RAW DATA: " << data;
       responseData.append(data);
       QString className = requestObject.className();
       qDebug() <<"DATA IN LIST: " <<responseData;
       fillXMLResponse(responseData, className);
       return result;
    }
}

// Destructor
ServerObjectResponse::~ServerObjectResponse(){

}
