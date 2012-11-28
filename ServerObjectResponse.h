/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef SERVEROBJECTRESPONSE_H
#define SERVEROBJECTRESPONSE_H

#include "ServerXMLResponse.h"
#include "StorableInterface.h"
#include "CUCareDatabase.h"
#include "ServerObjectRequest.h"


/*

  The purpose of the ServerObjectResponse is to take a request object
  and fill the request by performing the specified type of operation
  with it and the return the correct response to the client in the
  form of an object.

  */

class ServerObjectResponse : public ServerXMLResponse
{
public:
    CUCareDatabase * database;
    /*
      Creates a new TCPResponse object with the TCP Socket
      over which the data of the response will be sent
      */
    ServerObjectResponse(int TCPSocket, CUCareDatabase * db);
    /*
      Performs whatever has been requested in the request
      and returns the result of the request to the client
      over the tcp socket

            requestObject - The request being made that should be filled

            type - The type of request to be filled
    */
    int fillObjectResponse(StorableInterface& requestObject, ServerObjectRequest::ObjectRequestType type);
    // Destructor
    ~ServerObjectResponse();
};

#endif // SERVEROBJECTRESPONSE_H
