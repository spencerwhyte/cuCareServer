/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "CUCareServer.h"
#include <QTime>

/*
void testAddUser(){
    CUCareDatabase * database = new CUCareDatabase();
    User u;
    u.setUsername(new QString("spencerwhyte"));
    u.setUserType(User::Physician);
    if (database->addUser(u)){
         qDebug()<< "Added user successfully";
    }else{
        qDebug() << "Failed to add user";
    }

    if(database->authenticateUser(u)){
        qDebug() << "AnD the user authenticated";
    }else{
        qDebug() << "AND THE USER did not authenticate";
    }

}

void testAddPatient(){
    qDebug() << "BEGIN";
    CUCareDatabase*  database = new CUCareDatabase();
    qDebug() << "99";

    qDebug() << "76";


    QFile inputFile(":/input.txt");
        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);
           while ( !in.atEnd() )
           {
              PatientRecord p;
              QString line = in.readLine();
              qDebug() << line;
              p.setName(new QString(line));

              QString tempPhone("");
              for(int i = 0 ; i < 3 ; i++){
                  tempPhone.append(QString::number((qrand()%8) + 1));
              }

             tempPhone =  tempPhone.append("-");
              for(int i = 0 ; i < 3 ; i++){
                 tempPhone.append(QString::number((qrand()%8) + 1));
              }
               tempPhone.append("-");
              for(int i = 0 ; i < 4 ; i++){
                tempPhone.append(QString::number((qrand()%8) + 1));
              }


              p.setPhoneNumber(new QString(tempPhone));


              QString tempO("");
              for(int i = 0 ; i < 9 ; i++){
                  tempO = temsignals:

public slots:pO.append(QString::number((qrand()%8) + 1));
              }database
              p.setOHIPNumber(new QString(tempO));

              qDebug() << "34";
              database->addPatientRecord(p);

           }
        }
    inputFile.close();
    qDebug() << "23";
}
*/

void testServer(){
    CUCareServer * server= new CUCareServer();
}



Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));


   // testAddUser();
    //testAddPatient();

    testServer();

    return app->exec();
}


