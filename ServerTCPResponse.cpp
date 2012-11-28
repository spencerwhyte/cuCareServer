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
int fillTCPResponse(QString & data){

    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socket)) {
        emit error(tcpSocket.error());
        return;
    }

    tcpSocket.write(data);
    tcpSocket.waitForBytesWritten(5000);
    tcpSocket.disconnect();
}

// Destructor
~ServerTCPResponse(){

}









