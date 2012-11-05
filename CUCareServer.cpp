#include "CUCareServer.h"


CUCareServer::CUCareServer(QObject *parent){
    qDebug() << "Starting Server...";
    centralDatabase = new CUCareDatabase(this);

    if (!this->listen(QHostAddress::LocalHost,50000)) {
        qDebug() << "SERVER FAILED TO START";
        close();
        return;
    }

    qDebug() << this->serverPort();
    qDebug() << this->serverAddress();

    //connect(this, SIGNAL(incommingConnection()), this, SLOT(incomingConnections()));
    qDebug() << "Server Started";
}

void CUCareServer::incomingConnection(int socket){
    qDebug() << "Incoming Connection Recieved";
    CUCareServerThread *thread = new CUCareServerThread(socket, centralDatabase, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
