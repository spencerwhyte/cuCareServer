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

         StorableInterface * requestObject;
         ServerObjectRequest::ObjectRequestType type;

         ServerObjectRequest request(&TCPSocket);
         int result = request.fillObjectRequest(&requestObject, type);
         if(result == 0){
            ServerObjectResponse response(&TCPSocket, centralDatabase);
            response.fillObjectResponse(*requestObject, type);
            delete requestObject;
         }else{
             // Something failed when reading in the request
         }
         TCPSocket.disconnect();
}
