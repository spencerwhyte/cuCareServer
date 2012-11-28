/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERHTTPRESPONSE_H
#define SERVERHTTPRESPONSE_H

#include  "ServerTCPResponse.h"
#include <QString>

/*
  The purpose of this class is to take data and
  place it into an HTTP response and send it
  back to the client over TCP.
*/


class ServerHTTPResponse : public ServerTCPResponse
{
public:
    /*
      Constructs a ServerHTTPResponse with the TCP
      socket over which the response will be sent
    */
    ServerHTTPResponse(int TCPSocket);
    /*
      Takes the body and sends it back to the client
      as an HTTP response over TCP
      */
    int fillHTTPResponse(QString & body);
    // Destructor
    ~ServerHTTPResponse();

};

#endif // SERVERHTTPRESPONSE_H
