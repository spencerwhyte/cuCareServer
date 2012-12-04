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
    if(TCPSocket->state() == QAbstractSocket::ConnectedState){
          return 0;
    }
    return 1;
}

ServerTCPRequest::ServerTCPRequest(QTcpSocket * s) : TCPSocket(s) , allData(new QString()){

}


QString * ServerTCPRequest::getAllData(){
    return allData;
}

QTcpSocket * ServerTCPRequest::getTCPSocket(){
    return TCPSocket;
}

ServerTCPRequest::~ServerTCPRequest(){
    delete allData;
}
