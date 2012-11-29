/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "CUCareServerThread.h"


CUCareServerThread::CUCareServerThread(int s,CUCareDatabase * cd, QObject *parent){
    centralDatabase = cd;
    socket = s;
}

void CUCareServerThread::run(){
         qDebug() << "Request received, spawning thread to handle request";
         QTcpSocket TCPSocket;
         TCPSocket.setSocketDescriptor(socket);

         Record r;
         StorableInterface &requestObject = r;
         ServerObjectRequest::ObjectRequestType type;

         ServerObjectRequest request(&TCPSocket);
         request.fillObjectRequest(requestObject, type);

         ServerObjectResponse response(&TCPSocket, centralDatabase);
         response.fillObjectResponse(requestObject, type);

         TCPSocket.disconnect();
}
