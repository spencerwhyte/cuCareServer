#include "ServerObjectRequest.h"

// Constructs an request with the TCP Socket
// that the request will come over
ServerObjectRequest::ServerObjectRequest(QTcpSocket * TCPSocket) : ServerXMLRequest(TCPSocket){

}

/*
    Fills the request by transcribing the
    request into the appropriate object

        requestObject - The object sent as part
        of the request

        requestType - The type of request being
        performed

        returns - 0 for success
                  Any other number is the error code
  */
int ServerObjectRequest::fillObjectRequest(StorableInterface ** requestObject, ObjectRequestType & requestType){
    QString name;
    QMap<QString, QVariant> mapping;
    XMLRequestType xmlRequestType;

    int result = fillXMLRequest(mapping, name, xmlRequestType);

    if(result == 0){ // Success
        // Create the appropriate object from the XML data
        StorableInterface * ro = StorableFactory::GetFactory().getInstance(&name);
        ro->setAttributesAndValues(mapping);
        // Assign to output parameters

        *requestObject = ro;


        requestType = objectRequestTypeForXMLRequestType(xmlRequestType);
    }else{
        return result;
        qDebug() << "An error occured trying to fill the XML request, see ServerObjectRequest.cpp";
    }
    return 0;
}

ServerObjectRequest::ObjectRequestType ServerObjectRequest::objectRequestTypeForXMLRequestType(ServerXMLRequest::XMLRequestType type){
    if(type == ServerXMLRequest::Add){
        return Add;
    }else if(type == ServerXMLRequest::Edit){
         return Edit;
    }else if(type == ServerXMLRequest::Remove){
         return Remove;
    }else if(type == ServerXMLRequest::Query){
         return Query;
    }else if(type == ServerXMLRequest::EqualityQuery){
        return EqualityQuery;
    }
    qDebug() << "Assertion failure: Defaulted to Query in ServerObjectRequest.cpp";
    return Query;
}

// Destructor
ServerObjectRequest::~ServerObjectRequest(){

}
