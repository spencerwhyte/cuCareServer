#include "Record.h"

// Getters
int Record::getId(){
    return id;
}

// Setters
void Record::setId(int newID){
    id = newID;
}

// Constructor
Record::Record() : id(-1){

}

// Destructor
Record::~Record(){

}

// Supports compliance with the StorableInterface
void Record::getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const{
    attributesAndValues.insert(QString("id"),QVariant(id));
}
void Record::setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues){
    int tempID  = attributesAndValues.value(QString("id")).toInt();
    setId(tempID);
}

QString Record::className() const{
    static QString className("Record");
    return className;
}

QString Record::getIdentifierKey() const{
    static QString identifier;
    return identifier;
}
