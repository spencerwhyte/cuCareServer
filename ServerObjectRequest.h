/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVEROBJECTREQUEST_H
#define SERVEROBJECTREQUEST_H

#include "ServerXMLRequest.h"
#include "StorableInterface.h"
#include "StorableFactory.h"

/*
    The purpose of the ServerObjectRequest is to
    encapsulate all of the functionality having to
    do with transcribing a request on the server
    into an object
  */

class ServerObjectRequest : public ServerXMLRequest
{
public:
    typedef enum ObjectRequestType{
        Add,
        Edit,
        Remove,
        Query,
        EqualityQuery
    } ObjectRequestType;
    // Constructs an request with the TCP Socket
    // that the request will come over
    ServerObjectRequest(QTcpSocket * TCPSocket);
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
    int fillObjectRequest(StorableInterface ** requestObject, ObjectRequestType & requestType);

    ObjectRequestType objectRequestTypeForXMLRequestType(ServerXMLRequest::XMLRequestType type);

    // Destructor
    ~ServerObjectRequest();
};

#endif // SERVEROBJECTREQUEST_H
