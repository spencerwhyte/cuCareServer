#include "CUCareDatabase.h"



QSqlQuery CUCareDatabase::executeQuery(const QString& sql)
{
    qDebug() << sql;
    QSqlQuery query;
    query.exec(sql);
    qDebug() << query.lastError();
    return query;
}

bool CUCareDatabase::initializePatientTable(){
    executeQuery("create table patient "
                 "(id integer primary key, "
                 "firstname varchar(40), "
                 "lastname varchar(40), "
                 "ohip varchar (40))");

}

bool CUCareDatabase::initializeConsultationTable(){
    executeQuery("create table consultation "
                 "(id integer primary key, "
                 "firstname varchar(40), "
                 "lastname varchar(40), "
                 "ohip varchar (40))");
    return true;
}

bool CUCareDatabase::initializeUserTable(){
    executeQuery("create table user "
                 "(id integer primary key, "
                 "username varchar(40) ,"
                 "usertype varchar (40))");
    return true;
}


bool CUCareDatabase::initializeDatabase(){
    qDebug() << "Initializing Database...";
    initializePatientTable();
    initializeConsultationTable();
    initializeUserTable();
    qDebug() << "Database Initialized";
    return true;
}

 bool CUCareDatabase::addUser(const User& u){
     QString queryString = QString("INSERT into user (username, usertype) values (\"").append(u.getUsername()).append("\",\"").append(u.stringForUserType()).append("\")");
     QSqlQuery query = executeQuery(queryString);
     qDebug() << query.numRowsAffected();
     return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
 }

bool CUCareDatabase::isDatabaseInitialized(){
    QStringList l = db.tables();
    return (l.length() != 0);
}

void CUCareDatabase::createDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./cuCare.sqlite");
    bool result = db.open();
}

bool CUCareDatabase::authenticateUser(User& u){
    QSqlQuery query = executeQuery(QString("SELECT * FROM user WHERE username=\"").append(u.getUsername()).append("\""));
    if(query.next()){ // We found at least one result
        qDebug() << "USERTYPE: " << query.value(2).toString();
        u.setUserTypeForString(new QString(query.value(2).toString()));
        return true;
    }
    return false;
}

CUCareDatabase::CUCareDatabase(QObject *parent) :
    QObject(parent)
{
    createDatabase();
    if(!isDatabaseInitialized()){
        initializeDatabase();
    }

}

