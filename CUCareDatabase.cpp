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
int CUCareDatabase::addObject(StorableInterface & object){
    if(!isDatabaseTableInitialized(object.className())){
        initializeTableWithSchemaOfObject(object);
    }


    QMap<QString, QVariant> attributesAndValues;
    object.getAttributesAndValues(attributesAndValues);

    attributesAndValues.remove(object.getIdentifierKey());
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();

    QString queryString = QString("INSERT into ");
    queryString += object.className();
    queryString += " (";

    for(int i = 0 ; i < keys.length(); i++){
        queryString += keys.at(i);
        if(i != keys.length() -1){
            queryString += ", ";
        }
    }

    queryString += ") values (";

    for(int i = 0 ; i < keys.length(); i++){
        queryString += "?";
        if(i != keys.length() -1){
            queryString += ", ";
        }
    }
    queryString += ")";

    QSqlQuery query;
    query.prepare(queryString);
    for(int i = 0 ; i < values.length(); i++){
        query.addBindValue(values.at(i));
    }

    query.exec();

    int id = query.lastInsertId().toInt();

    attributesAndValues.insert(object.getIdentifierKey(), QVariant(id));
    object.setAttributesAndValues(attributesAndValues);


    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}

/*
    Updates the information pertaining to a particular object in the database

            object - The object whose information is to be updated
  */
int CUCareDatabase::editObject(StorableInterface & object){
    if(!isDatabaseTableInitialized(object.className())){
        initializeTableWithSchemaOfObject(object);
    }

    QMap<QString, QVariant> attributesAndValues;
    object.getAttributesAndValues(attributesAndValues);
    QVariant uniqueIdentifier = attributesAndValues.value(object.getIdentifierKey());
    attributesAndValues.remove(object.getIdentifierKey());
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();
    QString queryString = QString("UPDATE ");
    queryString += object.className();
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
int CUCareDatabase::removeObject(StorableInterface & object){
    if(!isDatabaseTableInitialized(object.className())){
        initializeTableWithSchemaOfObject(object);
    }

    QString queryString("DELETE FROM ");
    queryString += object.className();

    queryString += " WHERE id=?";

    QSqlQuery query;
    query.prepare(queryString);
    QMap<QString, QVariant> attributesAndValues;
    object.getAttributesAndValues(attributesAndValues);
    // Load them
    query.bindValue(0, attributesAndValues.value(object.getIdentifierKey()));
    query.exec();

    return !(query.numRowsAffected() == 0 || query.numRowsAffected() == -1);
}

/*
    Query's for all objects similar to the specified object

            object - The object to be queried for

            queryResults - Output parameter for the results
            of the query being requested
  */
int CUCareDatabase::queryForObjects(StorableInterface & object,  QList< QMap < QString, QVariant> > & queryResults, bool equality){
    if(!isDatabaseTableInitialized(object.className())){
        initializeTableWithSchemaOfObject(object);
    }
    QMap<QString, QVariant> attributesAndValues;
    object.getAttributesAndValues(attributesAndValues);
    attributesAndValues.remove(object.getIdentifierKey());
    QList<QString> keys = attributesAndValues.keys();
    QList<QVariant> values = attributesAndValues.values();


    QString queryString("SELECT * FROM ");
    queryString += object.className();
    bool first = true;
    for(int i =0 ; i < keys.length() ;i ++){
        if(((values.at(i).type() == QVariant::String) && values.at(i).toString().length() != 0 )||( (values.at(i).type() == QVariant::Int) && values.at(i).toInt() != -1 )){
            if(first){
                queryString += " WHERE ";
            }
            if(!first){
                queryString += " AND ";
            }
            first = false;
            queryString += keys.at(i);
            if(equality){
                queryString += " = ? ";

            }else{
                queryString += " LIKE '%' || ? || '%'";
            }
        }
    }

    QSqlQuery queryResult;
    queryResult.prepare(queryString);
    for(int i =0 ; i < keys.length() ;i ++){
        if(((values.at(i).type() == QVariant::String) && values.at(i).toString().length() != 0 )||( (values.at(i).type() == QVariant::Int) && values.at(i).toInt() != -1 )){
            queryResult.addBindValue(values.at(i).toString());
        }
    }
    queryResult.exec();


    while(queryResult.next()){
        QSqlRecord record = queryResult.record();
        QMap<QString, QVariant> current;
        for(int i = 0 ; i < record.count(); i++){
            QString attributeName = record.fieldName(i);
            QVariant value = record.field(i).value();
            current.insert(attributeName, value);
        }
        queryResults.append(current);
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

bool CUCareDatabase::isEmpty(){
    QStringList l = db.tables();
    if(l.size() == 0){
        return true;
    }
    return false;
}

bool CUCareDatabase::isDatabaseTableInitialized(QString className){
    QStringList l = db.tables();
    if(l.contains(className)){
        return true;
    }
    return false;
}

bool CUCareDatabase::initializeTableWithSchemaOfObject(StorableInterface & firstObject){
    QString schema("create table ");
    schema += firstObject.className();
    schema += " (id INTEGER PRIMARY KEY AUTOINCREMENT";
    QMap<QString, QVariant> attributesAndValues;
    firstObject.getAttributesAndValues(attributesAndValues);
    attributesAndValues.remove(firstObject.getIdentifierKey());

    QList<QString> keys = attributesAndValues.keys();

    QList<QVariant> values = attributesAndValues.values();

    for(int i = 0 ; i < keys.length(); i++){
        schema += ", ";
        schema += keys.at(i);
        QVariant::Type type = values.at(i).type();
        if(type == QVariant::String){
            schema += " varchar ";
        }else if(type == QVariant::Int){
            schema += " integer";
        }else if(type == QVariant::DateTime){
            schema += " DATETIME";
        }
    }

    schema += ")";

    executeQuery(schema);

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

    QSqlQuery query;
    query.exec(sql);

    return query;
}
