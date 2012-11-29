/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERXMLRESPONSE_H
#define SERVERXMLRESPONSE_H

#include "ServerHTTPResponse.h"
#include <QMap>
#include <QString>
#include <QVariant>
#include <QXmlStreamWriter>

/*
  The purpose of the ServerXMLResponse is to transribe
  response data into the XML format so that it may be
  sent over the network.
  */

class ServerXMLResponse : public ServerHTTPResponse
{
public:
    /*
      Constructs a new ServerXMlResponse with the TCP
      socket over which the data will be sent over
      */
    ServerXMLResponse(QTcpSocket * TCPSocket);
    /*
       Takes the mapping of attributes to values and the name of
       the response and turns it into XML data to be sent back
       to the client
      */
    int fillXMLResponse(QList< QMap<QString, QVariant> > & data, QString & name);
    // Destructor
    ~ServerXMLResponse();

};

#endif // SERVERXMLRESPONSE_H
