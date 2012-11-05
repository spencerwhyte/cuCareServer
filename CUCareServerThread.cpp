#include "CUCareServerThread.h"



CUCareServerThread::CUCareServerThread(int s,CUCareDatabase * cd, QObject *parent){
    centralDatabase = cd;
    socket = s;


}

void CUCareServerThread::run(){
         qDebug() << "Running";
         QTcpSocket tcpSocket;
         if (!tcpSocket.setSocketDescriptor(socket)) {
             emit error(tcpSocket.error());
             return;
         }

         HTTPRequest currentRequest(tcpSocket);
         tcpSocket.disconnect();
}
