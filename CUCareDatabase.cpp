/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "CUCareDatabase.h"


/*
    Adds an object to the database

            object - The object to be added
  */
int CUCareDatabase::addObject(StorableInterface * object){
    QMap<QString, QVariant> attributesAndValues;
    object->getAttributesAndValues(&attributesAndValues);
    attributesAndValues.remove(object->getIdentifierKey());
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();

    QString queryString = QString("INSERT into ");
    queryString += object->className();
    queryString += " (";

    for(int i = 0 ; i < keys.length(); i++){
        queryString += keys.at(i);
        if(i != keys.length() -1){
            queryString += ",";
        }
    }

    queryString += ") values (";

    for(int i = 0 ; i < keys.length(); i++){
        queryString += "?";
        if(i != keys.length() -1){
            queryString += ",";
        }
    }
    queryString += ")";

    QSqlQuery query;
    query.prepare(queryString);
    for(int i = 0 ; i < values.length(); i++){
         query.bindValue(i, values.at(i));
    }

    query.exec();

    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}

/*
    Updates the information pertaining to a particular object in the database

            object - The object whose information is to be updated
  */
int CUCareDatabase::editObject(StorableInterface * object){
    QMap<QString, QVariant> attributesAndValues;
    object->getAttributesAndValues(&attributesAndValues);
    QVariant uniqueIdentifier = attributesAndValues.value(object->getIdentifierKey());
    attributesAndValues.remove(object->getIdentifierKey());
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();
    QString queryString = QString("UPDATE ");
    queryString += object->className();
    queryString += " SET ";

    for(int i = 0 ; i < keys.length(); i++){
        queryString += keys.at(i);
        queryString += "=";
        queryString += "?";
        if(i != keys.length() -1){
            queryString += ",";
        }
    }

    queryString += " WHERE id=?";

    QSqlQuery query;
    query.prepare(queryString);
    for(int i = 0 ; i < values.length(); i++){
         query.bindValue(i, values.at(i));
    }

    query.bindValue(values.length(), uniqueIdentifier);

    query.exec();

    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}

/* Adds the object to the database
    Removes the given object from the database

            object - The object to be removed
  */
int CUCareDatabase::removeObject(StorableInterface * object){
    QString queryString("DELETE FROM ");
    queryString += object->className();

    queryString += " WHERE id=?";

    QSqlQuery query;
    query.prepare(queryString);
    QMap<QString, QVariant> attributesAndValues;
    object->getAttributesAndValues(&attributesAndValues);
    // Load them
    query.bindValue(0, attributesAndValues.value(object->getIdentifierKey()));
    query.exec();

    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}

/*
    Query's for all objects similar to the specified object

            object - The object to be queried for

            queryResults - Output parameter for the results
            of the query being requested
  */
int CUCareDatabase::queryForObjects(StorableInterface * object,  QList< QMap < QString, QVariant> > * queryResults){
    QMap<QString, QVariant> attributesAndValues;
    object->getAttributesAndValues(&attributesAndValues);
    attributesAndValues.remove(object->getIdentifierKey());
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();


    QString queryString("SELECT FROM ");
    queryString += object->className();

    queryString += " WHERE ";
    bool first = true;
    for(int i =0 ; i < keys.length() ;i ++){
        if((values.at(i).type() == QVariant::String) && values.at(i).toString().length() != 0){
            if(!first){
                queryString += " AND ";
            }
            first = false;
            queryString += " LIKE '%";
            queryString += keys.at(i);
            queryString += "%'";
        }
    }


    QSqlQuery queryResult = executeQuery(queryString);
    while(queryResult.next()){
        queryResults->append(queryResult.boundValues());
    }
    return true;
}

// Constructs the CUCareDatabase, giving it the name of the repository

CUCareDatabase::CUCareDatabase(QString * name, QObject *parent){
    createDatabase(name);
}

// Destructor
CUCareDatabase::~CUCareDatabase(){

}

bool CUCareDatabase::isDatabaseTableInitialized(QString * className){
    QStringList l = db.tables();
    if(l.contains(*className)){
        return true;
    }
    return false;
}

bool CUCareDatabase::initializeTableWithSchemaOfObject(StorableInterface * firstObject){
    QString schema("create table ");
    schema += firstObject->className();
    schema += " (id integer primary key";
    QMap<QString, QVariant> attributesAndValues;
    firstObject->getAttributesAndValues(&attributesAndValues);
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();

    for(int i = 0 ; i < keys.length(); i++){
        schema += ", ";
        schema += keys.at(i);
        QVariant::Type type = values.at(i).type();
        if(type == QVariant::String){
            schema += " varchar (1000) ";
        }else if(type == QVariant::Int){
            schema += " integer";
        }else if(type == QVariant::DateTime){
            schema += " DATETIME";
        }
    }
}

bool CUCareDatabase::createDatabase(QString * dn){
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString databaseName("./");
    databaseName = databaseName.append(*dn);
    databaseName = databaseName.append(".sqlite");
    db.setDatabaseName(databaseName);
    bool result = db.open();
}


QSqlQuery CUCareDatabase::executeQuery(const QString& sql){
    qDebug() << sql;
    QSqlQuery query;
    query.exec(sql);
    qDebug() << query.lastError();
    return query;
}



/*CUCareDatabase


bool CUCareDatabase::initializePatientTable(){
    executeQuery("create table patient "
                 "(id integer primary key, "
                 "name varchar(40), "
                 "phonenumber varchar(40), "
                 "ohipnumber varchar (40))");

}

bool CUCareDatabase::initializeConsultationTable(){
    executeQuery("create table consultation "
                 "(id integer primary key, "
                 "ohipnumber varchar(40), "
                 "dateandtime DATETIME, "
                 "diagnosis varchar (4000), "
                 "reason varchar (4000))");
    return true;
}

bool CUCareDatabase::addConsultationRecord(const ConsultationRecord &c){
    QString queryString = QString("INSERT into consultation ( ohipnumber, dateandtime, diagnosis, reason) values (?,?,?,?)");

    QSqlQuery query;

    query.prepare(queryString);

    if(c.hasOHIPNumber()){
        query.bindValue(0, *c.getOHIPNumber());
    }
    if(c.hasDateAndTime()){
        query.bindValue(1, c.getDateAndTime()->toString(Qt::ISODate));
    }
    if(c.hasReason()){
        query.bindValue(2, *c.getReason());
    }
    if(c.getDiagnosis()){
        query.bindValue(3, *c.getDiagnosis());
    }
    query.exec();

    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}

bool CUCareDatabase::editConsultationRecord(const ConsultationRecord &c){



    QString queryString = QString("UPDATE consultation SET ohipnumber= :on, dateandtime= :dt, diagnosis= :di, reason= :re WHERE id= :id ");
    qDebug() << "E1";
    QSqlQuery query;
    qDebug() << "E2";
    query.prepare(queryString);
    qDebug() << "E3";
    if(c.hasOHIPNumber()){
        qDebug() << "HAD OHIP NUMBER" << *c.getOHIPNumber();
        query.bindValue(":on", *c.getOHIPNumber());
    }cuCare
    if(c.hasDateAndTime()){
        qDebug() << "HAD DATE AND TIME: " << c.getDateAndTime()->toString(Qt::ISODate);
        query.bindValue(":dt", *c.getDateAndTime());
    }bool CUCareDatabase::isDatabaseInitialized(){
    QStringList l = db.tables();
    return (l.length() != 0);
}

void CUCareDatabase::createDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./cuCare.sqlite");
    bool result = db.open();
}


    if(c.hasDiagnosis()){
        qDebug() << "HAD DIAGNOSIS" << *c.getDiagnosis();
        query.bindValue(":di", *c.getDiagnosis());
    }
    qDebug() << "E5";
    if(c.hasReason()){
        qDebug() << "HAD REASON : " << *c.getReason();
        query.bindValue(":re", *c.getReason());
    }

    qDebug() << "E9";

    query.bindValue(":id",*c.getId());

 qDebug() << "E10";
    query.exec();

    qDebug() << query.lastError();
 qDebug() << "E19";
    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}
bool CUCareDatabase::isDatabaseInitialized(){
    QStringList l = db.tables();
    return (l.length() != 0);
} QString queryString = QString("INSERT into consultation ( ohipnumber, dateandtime, diagnosis, reason) values (?,?,?,?)");

    QSqlQuery query;

    query.prepare(queryString);

    if(c.hasOHIPNumber()){
        query.bindValue(0, *c.getOHIPNumber());
    }
    if(c.hasDateAndTime()){
        query.bindValue(1, c.getDateAndTime()->toString(Qt::ISODate));
    }
    if(c.hasReason()){
        query.bindValue(2, *c.getReason());
    }
    if(c.getDiagnosis()){
        query.bindValue(3, *c.getDiagnosis());
    }
    query.exec();

    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);

void CUCareDatabase::createDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./cuCare.sqlite");
    bool result = db.open();
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
    retubool CUCareDatabase::isDatabaseInitialized(){
    QStringList l = db.tables();
    return (l.length() != 0);
}

void CUCareDatabase::createDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./cuCare.sqlite");
    bool result = db.open();
}

rn true;
}

 bool CUCareDatabase::addUser(const User& u){
     QString queryString = QString("INSERT into user (username, usertype) values (\"").append(u.getUsername()).append("\",\"").append(u.stringForUserType()).append("\")");
     QSqlQuery query = executeQuery(queryString);
     qDebug() << query.numRowsAffected();
     return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
 }


 bool CUCareDatabase::addPatientRecord(const PatientRecord& p){
     qDebug() << "HERE";
     qDebug() << *p.getName();
     qDebug() << *p.getPhoneNumber();
     qDebug() << *p.getOHIPNumber();
     QString queryString("INSERT into patient (name, phonenumber, ohipnumber) values (");
     queryString.append("\"");
     queryString.append(*p.getName());
     queryString.append("\",\"");
     queryString.append(*p.getPhoneNumber());
     queryString.append("\",\"");
     queryString.append(*p.getOHIPNumber());
     queryString.append("\")");
     qDebug() << "HERE";

     QSqlQuery query = executeQuery(queryString);

     qDebug() << query.numRowsAffected();
     return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
 }




bool CUCareDatabase::authenticateUser(User& u){
    QSqlQuery query = executeQuery(QString("SELECT * FROM user WHERE username=\"").append(u.getUsername()).append("\""));
    if(query.next()){ // We found at least one result
        qDebug() << "USERCUCareServer * server, TYPE: " << query.value(2).toString();
        u.setUserTypeForString(new QString(query.value(2).toString()));
        return true;
    }
    return false;
}

bool CUCareDatabase::queryPatientRecord(PatientRecord & p,QList<PatientRecord> &list){
    QString query("SELECT * FROM patient");
    if(p.hasName() || p.hasOHIPNumber() || p.hasPhoneNumber()){
        query.append(" WHERE ");
        if(p.hasName()){
            query.append("name like \"%").append(*p.getName()).append("%\" ");
        }
        if(p.hasPhoneNumber()){
            if(p.hasName()){
                query.append(" AND ");
            }
            query.append("phonenumbe    // Constructor
    CUCareServer();r like \"%").append(*p.getPhoneNumber()).append("%\" ");
        }
        if(p.hasOHIPNumber()){
            if(p.hasName() || p.hasPhoneNumber()){
                query.append(" AND ");
            }
            query.append("ohipnumber like \"%").append(*p.getOHIPNumber()).append("%\" ");
        }
    }
    QSqlQuery queryResult = executeQuery(query);
    while(queryResult.next()){
        PatientRecord  * currentP = new PatientRecord();
        currentP->setName(new QString(queryResult.value(1).toString()));
        currentP->setPhoneNumber(new QString(queryResult.value(2).toString()));
        currentP->setOHIPNumber(new QString(queryResult.value(3).toString()));
        list.append(*currentP);

    }
    return true;
}


bool CUCareDatabase::queryConsultationRecord(ConsultationRecord & c,QList<ConsultationRecord> &list){
    QString query("SELECT * FROM consultation");
    if(c.hasOHIPNumber()){
        query.append(" WHERE ");
        if(c.hasOHIPNumber()){
            query.append("ohipnumb    // Constructor
    CUCareServer();er = \"").append(*c.getOHIPNumber()).append("\" ");
        }
    }

    QSqlQuery queryResult = executeQuery(query);

    while(queryResult.next()){
        ConsultationRecord  * current = new ConsultationRecord();

        current->setId(new QString(queryResult.value(0).toString()));
        current->setOHIPNumber(new QString(queryResult.value(1).toString()));
        current->setDateAndTime(new QDateTime(queryResult.value(2).toDateTime()));
        current->setDiagnosis(new QString(queryResult.value(3).toString()));
        current->setReason(new QString(queryResult.value(4).toString()));

        list.append(*current);

    }
    return true;
}

CUCareDatabase::CUCareDatabase(QObject *parent) :
    QObject(parent)
{
    createDatabase();
    if(!isDatabaseInitialized()){
        initializeDatabase();
    }

}


*/
