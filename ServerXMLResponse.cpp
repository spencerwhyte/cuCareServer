#include "ServerXMLResponse.h"

/*
  Constructs a new ServerXMlResponse with the TCP
  socket over which the data will be sent over
  */
ServerXMLResponse::ServerXMLResponse(QTcpSocket * TCPSocket) : ServerHTTPResponse(TCPSocket){

}

/*
   Takes the mapping of attributes to values and the name of
   the response and turns it into XML data to be sent back
   to the client
  */
int ServerXMLResponse::fillXMLResponse(QList< QMap<QString, QVariant> > & data, QString & name){
    QString body;
    QXmlStreamWriter writer(&body);
    writer.writeStartDocument();
    writer.writeStartElement("list");

    for(int i = 0 ; i < data.length(); i++){
        QMap<QString, QVariant> currentData = data.at(i);
        writer.writeStartElement(name);
        QList<QString> keys = currentData.keys();
        QList<QVariant> values = currentData.values();
        for(int i = 0 ; i < keys.length(); i++){
            writer.writeTextElement(keys.at(i), values.at(i).toString());
        }
        writer.writeEndElement();
    }

    writer.writeEndElement();

    int result = fillHTTPResponse(body);
}

// Destructor
ServerXMLResponse::~ServerXMLResponse(){

}
