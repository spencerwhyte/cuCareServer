/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "CUCareServer.h"

void CUCareServer::populateServerTest(CUCareDatabase *database){

    QFile f("randomNames.csv");
    if (f.open(QIODevice::ReadOnly))
    {
     //file opened successfully
     QString data;
     data = f.readAll();
     QStringList vals = data.split('\n');

     for(int i =0 ;i < 9500; i++){
         if(vals.at(i).length() != 0){
              PatientRecord p;

              p.setName(vals.at(i));

              p.setOHIPNumber(QString::number(314159 + i));

              p.setPrimaryPhysician(QString("Spencer Whyte"));

              QString phoneNumber;

              for(int j = 0; j < 3; j++){
                  phoneNumber+= QString::number(((i+j)%8)+1);
              }
              phoneNumber += "-";
              for(int j = 0; j < 3; j++){
                   phoneNumber+=QString::number( ((i+j)* 23%8)+1 );
              }
              phoneNumber += "-";
              for(int j = 0; j < 4; j++){
                   phoneNumber+=QString::number(((i+j* 7)%8)+1);
              }

              p.setPhoneNumber(phoneNumber);



              centralDatabase->addObject(p);


             qDebug() << vals.at(i);
         }
     }


     f.close();
    }



}


CUCareServer::CUCareServer(QObject *parent){
    qDebug() << "Starting Server...";
    centralDatabase = new CUCareDatabase(new QString("cuCare"), this);


   populateServerTest(centralDatabase);



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

