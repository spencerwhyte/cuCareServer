#include "ServerTCPResponse.h"

/*
  Creates a TCPResponse object with the TCP socket
  over which the response will be sent
  */
ServerTCPResponse::ServerTCPResponse(int TCPSocket) : socket(TCPSocket){

}

/*
  Fills the TCP response by sending the data back to
  the client over TCP

        data - Input parameter of the data to be sent
        over TCP to the client
  */
int ServerTCPResponse::fillTCPResponse(QString & data){

    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socket)) {
        return 1;
    }
    QByteArray byteArrayOfData;
    byteArrayOfData.append(data);
    tcpSocket.write(byteArrayOfData);
    tcpSocket.waitForBytesWritten(5000);
    tcpSocket.disconnect();
    return 0;
}

// Destructor
ServerTCPResponse::~ServerTCPResponse(){

}









