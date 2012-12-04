/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "CUCareServer.h"



CUCareServer::CUCareServer(QObject *parent) : jobManager (new ServerScheduledJobManager()){
    qDebug() << "Starting Server...";
    centralDatabase = new CUCareDatabase(new QString("cuCare"), this);

    if(centralDatabase->isEmpty()){ // If the server is empty, populate it for the TA
        populateServerTest(centralDatabase);
    }

    if (!this->listen(QHostAddress::Any,60007)) {
        qDebug() << "SERVER FAILED TO START";
        close();
        return;
    }

    AuditProcessManager * aup = new AuditProcessManager(centralDatabase);
    //PatientAuditProcessManager * papm = new PatientAuditProcessManager(centralDatabase);

    jobManager->scheduleJob(aup);
    //jobManager->scheduleJob(papm);

    qDebug() << this->serverPort();
    qDebug() << this->serverAddress();

    qDebug() << "Server Started";
}

CUCareServer::~CUCareServer(){
    delete jobManager;
}

void CUCareServer::incomingConnection(int socket){
    qDebug() << "Incoming Connection Recieved";
    CUCareServerThread * thread = new CUCareServerThread(socket, centralDatabase, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}


void CUCareServer::populateServerTest(CUCareDatabase *database){
    qDebug() << "INITIALIZING SERVER";

    User u;
    u.setUsername("Spencer Whyte");
    u.setUserType(User::Physician);
    database->addObject(u);

    User u2;
    u2.setUsername("Z");
    u2.setUserType(User::Physician);
    database->addObject(u2);

    //ADD: Consultation 1
    ConsultationRecord consult;
    consult.setDiagnosis(QString("Cancer!"));
    consult.setOHIPNumber(QString("314159"));
    consult.setReason(QString("We thought they had cancer"));
    consult.setDateAndTime(QDateTime::currentDateTime().addDays(-2));
    database->addObject(consult);

    FollowUpRecord follow;
    follow.setConsultationRecordId(1);
    follow.setStatus(FollowUpRecord::PENDING);
    follow.setDueDateTime(QDateTime::currentDateTime()); // Sets date and time to right now
    follow.setDetails(QString("You require more minerals"));
    database->addObject(follow);

    FollowUpRecord follow2;
    follow2.setConsultationRecordId(1);
    follow2.setStatus(FollowUpRecord::PENDING);
    follow2.setDueDateTime(QDateTime::currentDateTime().addDays(2)); // Sets date and time to right now
    follow2.setDetails(QString("You require more Vespene gas"));
    database->addObject(follow2);

    FollowUpRecord follow3;
    follow3.setConsultationRecordId(1);
    follow3.setStatus(FollowUpRecord::PENDING);
    follow3.setDueDateTime(QDateTime::currentDateTime().addDays(4)); // Sets date and time to right now
    follow3.setDetails(QString("You must construct additional pylons"));
    database->addObject(follow3);

    //ADD: Consultation 2
    ConsultationRecord consult2;
    consult2.setDiagnosis(QString("Lupus!"));
    consult2.setOHIPNumber(QString("314159"));
    consult2.setReason(QString("We thought they had lupus"));
    consult2.setDateAndTime(QDateTime::currentDateTime().addDays(-5));
    database->addObject(consult2);

    FollowUpRecord follow4;
    follow4.setConsultationRecordId(1);
    follow4.setStatus(FollowUpRecord::COMPLETE);
    follow4.setDueDateTime(QDateTime().addMonths(2)); // Sets date and time to right now
    follow4.setDetails(QString("You require more time"));
    database->addObject(follow4);

    FollowUpRecord follow5;
    follow5.setConsultationRecordId(1);
    follow5.setStatus(FollowUpRecord::COMPLETE);
    follow5.setDueDateTime(QDateTime().addDays(11)); // Sets date and time to right now
    follow5.setDetails(QString("You require more mana"));
    database->addObject(follow5);

    FollowUpRecord follow6;
    follow6.setConsultationRecordId(1);
    follow6.setStatus(FollowUpRecord::PENDING);
    follow6.setDueDateTime(QDateTime().addDays(-10)); // Sets date and time to right now
    follow6.setDetails(QString("It's never lupus"));
    database->addObject(follow6);

    //ADD: Consultation 3
    ConsultationRecord consult3;
    consult3.setDiagnosis(QString("Friends!"));
    consult3.setOHIPNumber(QString("314159"));
    consult3.setReason(QString("We thought they wanted to be friends"));
    consult3.setDateAndTime(QDateTime().addDays(-10));
    database->addObject(consult3);

    FollowUpRecord follow7;
    follow7.setConsultationRecordId(1);
    follow7.setStatus(FollowUpRecord::COMPLETE);
    follow7.setDueDateTime(QDateTime().addMonths(1)); // Sets date and time to right now
    follow7.setDetails(QString("You require more minerals"));
    database->addObject(follow7);

    FollowUpRecord follow8;
    follow8.setConsultationRecordId(1);
    follow8.setStatus(FollowUpRecord::COMPLETE);
    follow8.setDueDateTime(QDateTime().addMonths(5)); // Sets date and time to right now
    follow8.setDetails(QString("You require more Vespene gas"));
    database->addObject(follow8);

    FollowUpRecord follow9;
    follow9.setConsultationRecordId(1);
    follow9.setStatus(FollowUpRecord::PENDING);
    follow9.setDueDateTime(QDateTime::currentDateTime()); // Sets date and time to right now
    follow9.setDetails(QString("You must construct additional pylons"));
    database->addObject(follow9);

    QFile f(":/new/coolidentifier/randomNames.csv");
    if (f.open(QIODevice::ReadOnly))
    {
     //file opened successfully
     QString data;
     data = f.readAll();
     QStringList vals = data.split('\n');

     for(int i =1 ;i < 100; i++){
         if(vals.at(i).length() != 0){
              PatientRecord p;

              p.setName(vals.at(i));

              p.setOHIPNumber(QString::number(314159 + i - 1));

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

            // qDebug() << vals.at(i);
         }
     }


     f.close();
    }



}

