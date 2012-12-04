#include "ServerTCPResponse.h"

/*
  Creates a TCPResponse object with the TCP socket
  over which the response will be sent
  */
ServerTCPResponse::ServerTCPResponse(QTcpSocket * TCPSocket) : socket(TCPSocket){

}

/*
  Fills the TCP response by sending the data back to
  the client over TCP

        data - Input parameter of the data to be sent
        over TCP to the client
  */
int ServerTCPResponse::fillTCPResponse(QString & data){
    QByteArray byteArrayOfData;
    byteArrayOfData.append(data);
    getSocket()->write(byteArrayOfData);
    getSocket()->waitForBytesWritten(5000);
    getSocket()->disconnect();
    return 0;
}

QTcpSocket * ServerTCPResponse::getSocket(){
    return socket;
}

// Destructor
ServerTCPResponse::~ServerTCPResponse(){

}









