/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERXMLREQUEST_H
#define SERVERXMLREQUEST_H

#include "ServerHTTPRequest.h"
#include <QMap>
#include <QString>
#include <QVariant>
#include <QDomDocument>
#include <QStringList>

/*
  The server XMLRequest is responsible for transcribing
  XML request data into a key value mapping that can be
  used by inheriting classes to provide additional
  transcription
  */

class ServerXMLRequest : public ServerHTTPRequest
{
public:
    typedef enum XMLRequestType{
        Add,
        Edit,
        Remove,
        Query
    }XMLRequestType;
    /*
      Constructs a ServerXMLRequest

            TCPSocket - The TCP socket over which the
            request will come
      */
    ServerXMLRequest(int TCPSocket);
    /*
      Fills an XML request by transcribing the XML
      request data into an key/value mapping and
      preserving the type of the request. All
      parameters are OUTPUT parameters.

            xmlMapping - A key value mapping that maps
            the keys and values from the XML

            name - The name corresponding to the XML
            request

            type - The type of XML request taking place
    */
    int fillXMLRequest(QMap<QString, QVariant> & xmlMapping, QString & name, XMLRequestType & type);
    // Destructor
    ~ServerXMLRequest();

private:
    /*
      Extracts the xml request type from a given url

            type - Output parameter to store the type of request

            url - Input parameter that contains the url

            returns - 0 On success
                      Any other number is the error code
      */
    int requestTypeForUrl(XMLRequestType &type, const QString & url);

    /*
      Extracts the class name of the request object from the url

            name - Output parameter to store the name of the class

            url - Input parameter that contains the url

            returns - 0 On success
                      Any other number is the error code
      */
    int classNameForUrl(QString &name, const QString & url);


    /*
      Constructs a key/value mapping from XML data with the given root node name
      This method does not produce a true tree but rather a very short tree
      containing the key/value mapping within a particular node

            xmlMapping - Output parameter for the xml mapping that will be
                         created

            xmlData - The raw XML data to be used

            rootNodeName - The name of the root node at which the map will be
                           constructed from

            returns - 0 On success
                      Any other number is the error code
      */
    int xmlMappingForDataAndRootNode(QMap<QString, QVariant> &xmlMapping, const QString & xmlData, const QString&rootNodeName);
};

#endif // SERVERXMLREQUEST_H
