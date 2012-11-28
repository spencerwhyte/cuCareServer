#include "ServerTCPRequest.h"


// Getters
QString * ServerTCPRequest::getTCPData(){
    return allData;
}

/*
  Attempts to fill the TCP request by filling it's
  buffer with the latest tcp data that has been
  received.

        returns - 0 for success
                  Any other number will be the error code
 */
int ServerTCPRequest::fillTCPRequest(){

    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(TCPSocket)) {

        return 1;
    }

    if(tcpSocket.waitForReadyRead(50)){

        QByteArray readData = tcpSocket.readAll();
        allData->append(readData);

    }
    return 0;

}

ServerTCPRequest::ServerTCPRequest(int s) : TCPSocket(s) , allData(new QString()){

}

ServerTCPRequest::~ServerTCPRequest(){
    delete allData;
}
