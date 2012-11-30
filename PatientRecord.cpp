/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "PatientRecord.h"


// Getters
QString  PatientRecord::getName() const{
    return *name;
}

QString  PatientRecord::getPhoneNumber() const{
    return *phoneNumber;
}

QString  PatientRecord::getOHIPNumber() const{
    return *OHIPNumber;
}

QString  PatientRecord::getPrimaryPhysician() const{
    return *primaryPhysician;
}


bool PatientRecord::getHasOverDueFollowUps()const{
    return hasOverDueFollowUps;
}

bool PatientRecord::getHasPendingFollowUps()const{
    return hasPendingFollowUps;
}

bool PatientRecord::getHasCompletedFollowUps()const{
    return hasCompletedFollowUps;
}

// Setters
void  PatientRecord::setName(QString  newName){
    delete name;
    name = new QString(newName);
}

void  PatientRecord::setPhoneNumber(QString  newPhoneNumber){
    delete phoneNumber;
    phoneNumber = new QString(newPhoneNumber);
}

void PatientRecord::setOHIPNumber(QString  newOhipNumber){
    delete OHIPNumber;
    OHIPNumber = new QString(newOhipNumber);
}

void PatientRecord::setPrimaryPhysician(QString  newPrimaryPhysician){
    delete primaryPhysician;
    primaryPhysician = new QString(newPrimaryPhysician);
}

void PatientRecord::setHasOverDueFollowUps(bool newValue){
    hasOverDueFollowUps = newValue;
}

void PatientRecord::setHasPendingFollowUps(bool newValue){
    hasPendingFollowUps = newValue;
}

void PatientRecord::setHasCompletedFollowUps(bool newValue){
    hasCompletedFollowUps = newValue;
}


// Storable Interface Methods
void PatientRecord::getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues.insert(QString("Name"), QVariant(QString(getName())));
    attributesAndValues.insert(QString("PhoneNumber"), QVariant(QString(getPhoneNumber())));
    attributesAndValues.insert(QString("OHIPNumber"), QVariant(QString(getOHIPNumber())));
    attributesAndValues.insert(QString("PrimaryPhysician"), QVariant(QString(getPrimaryPhysician())));

    attributesAndValues.insert(QString("HasOverDueFollowUps"), QVariant(getHasOverDueFollowUps()));
    attributesAndValues.insert(QString("HasPendingFollowUps"), QVariant(getHasPendingFollowUps()));
    attributesAndValues.insert(QString("HasCompletedFollowUps"), QVariant(getHasCompletedFollowUps()));
}

void PatientRecord::setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString  n = attributesAndValues.value(QString("Name")).toString();
    QString  p = attributesAndValues.value(QString("PhoneNumber")).toString();
    QString  o = attributesAndValues.value(QString("OHIPNumber")).toString();
    QString  ps = attributesAndValues.value(QString("PrimaryPhysician")).toString();

    bool hf = attributesAndValues.value(QString("HasOverDueFollowUps")).toBool();
    bool pf = attributesAndValues.value(QString("HasPendingFollowUps")).toBool();
    bool cf = attributesAndValues.value(QString("HasCompletedFollowUps")).toBool();


    setName(n);
    setPhoneNumber(p);
    setOHIPNumber(o);
    setPrimaryPhysician(ps);

    setHasOverDueFollowUps(hf);
    setHasPendingFollowUps(pf);
    setHasCompletedFollowUps(cf);
}

QString PatientRecord::className() const{
    static QString className("PatientRecord");
    return className;
}

// Constructor and destructor
PatientRecord::PatientRecord(): name(new QString()), phoneNumber(new QString()), OHIPNumber(new QString()), primaryPhysician(new QString()),hasOverDueFollowUps(false), hasPendingFollowUps(false), hasCompletedFollowUps(false){

}

PatientRecord::~PatientRecord(){
    delete name;
    delete phoneNumber;
    delete OHIPNumber;
    delete primaryPhysician;
}
