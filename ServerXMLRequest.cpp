#include "ServerXMLRequest.h"

/*
  Constructs a ServerXMLRequest

        TCPSocket - The TCP socket over which the
        request will come
  */
ServerXMLRequest::ServerXMLRequest(int TCPSocket) : ServerHTTPRequest(TCPSocket){

}

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
int ServerXMLRequest::fillXMLRequest(QMap<QString, QVariant> &xmlMapping, QString &name, XMLRequestType &type){

    QString body;
    QString url;

    requestTypeForUrl(type, url);

    classNameForUrl(name,url);

    int result = this->fillHTTPRequest(body, url);

    if(result == 0){

        xmlMappingForDataAndRootNode(xmlMapping, body, name);

    }else{
        return result;
    }

}

/*
  Extracts the xml request type from a given url

        type - Output parameter to store the type of request

        url - Input parameter that contains the url

        returns - 0 On success
                  Any other number is the error code
  */
int ServerXMLRequest::requestTypeForUrl(XMLRequestType &type, const QString & url){
    QStringList components = url.split(QString("/"));
    QString typeString = components.at(0);
    if(typeString.compare(typeString, QString("Add"), Qt::CaseInsensitive) == 0){
        type = Add;
        return 0;
    }else if(typeString.compare(typeString, QString("Edit"), Qt::CaseInsensitive) == 0){
        type = Edit;
        return 0;
    }else if(typeString.compare(typeString, QString("Query"), Qt::CaseInsensitive) == 0){
        type = Query;
        return 0;
    }else if(typeString.compare(typeString, QString("Remove"), Qt::CaseInsensitive) == 0){
        type = Remove;
        return 0;
    }
    return 1;
}

/*
  Extracts the class name of the request object from the url

        name - Output parameter to store the name of the class

        url - Input parameter that contains the url

        returns - 0 On success
                  Any other number is the error code
  */
int ServerXMLRequest::classNameForUrl(QString &name, const QString & url){
    QStringList components = url.split(QString("/"));
    name = components.at(1);
    if(name.length() > 0){
        return 0;
    }
    return 1;
}

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
int ServerXMLRequest::xmlMappingForDataAndRootNode(QMap<QString, QVariant> &xmlMapping, const QString & xmlData, const QString&rootNodeName){

    QDomDocument doc("XMLRequest");
    doc.setContent(xmlData);

    QDomElement root = doc.firstChildElement(rootNodeName);

    QDomNodeList keyValues = root.childNodes();

    for(int i = 0; i< keyValues.length(); i++){
        QDomNode node = keyValues.at(i);
        xmlMapping.insert(node.nodeName(), QVariant(node.nodeValue()));
    }

    return 0;

}



// Destructor
ServerXMLRequest::~ServerXMLRequest(){

}
