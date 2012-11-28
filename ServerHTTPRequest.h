/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERHTTPREQUEST_H
#define SERVERHTTPREQUEST_H

#include "ServerTCPRequest.h"

/*
  The purpose of the ServerHTTPRequest is to transcribe
  HTTP requests by extracting the body of the request
  and the url to which the request is being made
 */

class ServerHTTPRequest : public ServerTCPRequest
{ 
public:
   /*
     Creates a new ServerHTTPRequest that will handle
     data coming over the TCP socket

        TCPSocket - The socket over which information
        will be transferred
     */
    ServerHTTPRequest(int TCPSocket);
    /*
     Fills the ServerHTTPRequest by extracting the body
     and the url from the HTTP request.

            httpBody - Output parameter to hold the
            data that came in the body of the HTTP
            request.

            url - Output parameter to hold the url
            of the request
      */
    int fillHTTPRequest(QString& httpBody, QString& url);

    // Destructor
    ~ServerHTTPRequest();
};

#endif // SERVERHTTPREQUEST_H
