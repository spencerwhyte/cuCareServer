/*
  By: Spencer Whyte
  # 100817664
  Carleton University
*/

#ifndef SERVERTCPREQUEST_H
#define SERVERTCPREQUEST_H
#include <QString>
#include <QTcpSocket>

/*
  The purpose of the ServerTCPRequest is to transcribe
  data being transferred over a TCP socket into a form
  that is useful to inheriting classes.
  */

class ServerTCPRequest
{
    // Holds all of the data that has been received
    // by the tcp socket so far
    QString * allData;
    // The TCP socket over which all of the request
    // data comes
    int TCPSocket;
public:
    // Getters
    QString * getTCPData();
    /*
      Attempts to fill the TCP request by filling it's
      buffer with the latest tcp data that has been
      received.

            returns - 0 for success
                      Any other number will be the error code
     */
    int fillTCPRequest();

    ServerTCPRequest(int TCPSocket);
    ~ServerTCPRequest();

};

#endif // SERVERTCPREQUEST_H
