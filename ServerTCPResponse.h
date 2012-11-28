/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERTCPRESPONSE_H
#define SERVERTCPRESPONSE_H

#include <QString>

/*
  The purpose of this class is to handle sending
  tcp data back to the client over TCP.
  */
class ServerTCPResponse
{
public:
    /*
      Creates a TCPResponse object with the TCP socket
      over which the response will be sent
      */
    ServerTCPResponse(int TCPSocket);
    /*
      Fills the TCP response by sending the data back to
      the client over TCP

            data - Input parameter of the data to be sent
            over TCP to the client
      */
    int fillTCPResponse(QString * data);
    // Destructor
    ~ServerTCPResponse();
};

#endif // SERVERTCPRESPONSE_H
