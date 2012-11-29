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

    if(TCPSocket->waitForReadyRead(50)){

        QByteArray readData = TCPSocket->readAll();
        allData->append(readData);

    }
    return 0;

}

ServerTCPRequest::ServerTCPRequest(QTcpSocket * s) : TCPSocket(s) , allData(new QString()){

}

ServerTCPRequest::~ServerTCPRequest(){
    delete allData;
}
