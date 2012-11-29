/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "CUCareServer.h"


CUCareServer::CUCareServer(QObject *parent){
    qDebug() << "Starting Server...";
    centralDatabase = new CUCareDatabase(new QString("cuCare"), this);

    if (!this->listen(QHostAddress::Any,60007)) {
        qDebug() << "SERVER FAILED TO START";
        close();
        return;
    }

    qDebug() << this->serverPort();
    qDebug() << this->serverAddress();

    qDebug() << "Server Started";
}

void CUCareServer::incomingConnection(int socket){
    qDebug() << "Incoming Connection Recieved";
    CUCareServerThread *thread = new CUCareServerThread(socket, centralDatabase, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

