/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "PatientRecord.h"


// Getters
QString * PatientRecord::getName() const{
    return name;
}

QString * PatientRecord::getPhoneNumber() const{
    return phoneNumber;
}

QString * PatientRecord::getOHIPNumber() const{
    return OHIPNumber;
}

// Setters
void  PatientRecord::setName(QString * newName){
    delete name;
    name = newName;
}

void  PatientRecord::setPhoneNumber(QString * newPhoneNumber){
    delete phoneNumber;
    phoneNumber = newPhoneNumber;
}

void PatientRecord::setOHIPNumber(QString * newOhipNumber){
    delete OHIPNumber;
    OHIPNumber = newOhipNumber;
}

// Storable Interface Methods
void PatientRecord::getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues.insert(QString("Name"), QVariant(QString(*getName())));
    attributesAndValues.insert(QString("PhoneNumber"), QVariant(QString(*getPhoneNumber())));
    attributesAndValues.insert(QString("OHIPNumber"), QVariant(QString(*getOHIPNumber())));
}

void PatientRecord::setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString * n = new QString( attributesAndValues.value(QString("Name")).toString());
    QString * p = new QString( attributesAndValues.value(QString("PhoneNumber")).toString());
    QString * o = new QString( attributesAndValues.value(QString("OHIPNumber")).toString());

    setName(n);
    setPhoneNumber(p);
    setOHIPNumber(o);
}

QString PatientRecord::className() const{
    static QString className("PatientRecord");
    return className;
}

// Constructor and destructor
PatientRecord::PatientRecord(): name(new QString()), phoneNumber(new QString()), OHIPNumber(new QString()){

}

PatientRecord::~PatientRecord(){
    delete name;
    delete phoneNumber;
    delete OHIPNumber;
}
