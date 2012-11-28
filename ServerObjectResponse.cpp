#include "ServerObjectResponse.h"

/*
  Creates a new TCPResponse object with the TCP Socket
  over which the data of the response will be sent
  */
ServerObjectResponse::ServerObjectResponse(int TCPSocket, CUCareDatabase * db) : ServerXMLResponse(TCPSocket) , database(db){

}

/*
  Performs whatever has been requested in the request
  and returns the result of the request to the client
  over the tcp socket

        requestObject - The request being made that should be filled

        type - The type of request to be filled
*/
int ServerObjectResponse::fillObjectResponse(StorableInterface& requestObject, ServerObjectRequest::ObjectRequestType type){



   if(type == ServerObjectRequest::Query){
        QList<QMap<QString, QVariant> > responseData;

        int result = database->queryForObjects(requestObject, responseData);

        fillXMLResponse(responseData, requestObject.className());

        return result;
    }else{
       int result;

       QList<QMap<QString, QVariant> > responseData;
       QMap<QString, QVariant> data;
       requestObject.getAttributesAndValues(data);
       responseData.append(data);

       if(type == ServerObjectRequest::ObjectRequestType::Add){
            result = database->addObject(requestObject);
       }else if(type == ServerObjectRequest::Edit){
            result = database->editObject(requestObject);
       }else if(type == ServerObjectRequest::Remove){
            result = database->removeObject(requestObject);
       }
       fillXMLResponse(responseData, requestObject.className());
       return result;
    }
}

// Destructor
ServerObjectResponse::~ServerObjectResponse(){

}
