#ifndef CUCAREDATABASE_H
#define CUCAREDATABASE_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QtCore/QCoreApplication>

#include <QtSql>
#include <QtSql/QSqlQuery>
#include "PatientRecord.h"
#include "User.h"
#include "ConsultationRecord.h"



class CUCareDatabase : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase db;

    void createDatabase();

    explicit CUCareDatabase(QObject *parent = 0);

    QSqlQuery executeQuery(const QString& sql);

    /**********************
      Database Initialization
      *****************/
    bool isDatabaseInitialized();

    bool initializePatientTable();

    bool initializeConsultationTable();

    bool initializeUserTable();

    bool initializeDatabase();

    /**************
      PatientRecord
      **************/
    bool addPatientRecord(const PatientRecord& p);

    bool updatePatientRecord(const PatientRecord& p);
    /***************
      User
      **************/
    bool addUser(const User& u);

    bool removeUser(const User& u);

    bool authenticateUser(User& u);

    /**************
    Consultation Record
      ****************/
    bool addConsultationRecord(const ConsultationRecord &c);

    bool updateConsultationRecord(const ConsultationRecord &c);

    /********************
       Database Queries
     ********************/
protected:

signals:
    
public slots:

};

#endif // CUCAREDATABASE_H
