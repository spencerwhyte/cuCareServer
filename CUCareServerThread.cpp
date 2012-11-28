/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "CUCareServerThread.h"
#include "ServerObjectRequest.h"
#include "ServerObjectResponse.h"

CUCareServerThread::CUCareServerThread(int s,CUCareDatabase * cd, QObject *parent){
    centralDatabase = cd;
    socket = s;
}

void CUCareServerThread::run(){
         qDebug() << "Request received, spawning thread to handle request";
         StorableInterface requestObject;
         ServerObjectRequest::ObjectRequestType type;

         ServerObjectRequest request(socket);
         request.fillObjectRequest(requestObject, type);

         ServerObjectResponse response(socket, centralDatabase);
         response.fillObjectResponse(requestObject, type);


}
