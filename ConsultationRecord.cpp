/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "ConsultationRecord.h"

QDateTime * ConsultationRecord::getDateAndTime() const{
    return dateAndTime;
}

QString * ConsultationRecord::getReason() const {
    return reason;
}

QString * ConsultationRecord::getOHIPNumber() const{
    return OHIPNumber;
}

QString * ConsultationRecord::getDiagnosis() const{
    return diagnosis;
}

void  ConsultationRecord::setDateAndTime(QDateTime * newDateAndTime){
    delete getDateAndTime();
    dateAndTime = newDateAndTime;
}

void  ConsultationRecord::setReason(QString* newReason){
    delete getReason();
    reason = newReason;
}

void  ConsultationRecord::setOHIPNumber(QString* newOHIPNumber){
    delete getOHIPNumber();
    OHIPNumber = newOHIPNumber;
}

void  ConsultationRecord::setDiagnosis(QString* newDiagnosis){
    delete getDiagnosis();
    diagnosis = newDiagnosis;
}


ConsultationRecord::ConsultationRecord(): dateAndTime(new QDateTime), reason(new QString()), OHIPNumber(new QString()), diagnosis(new QString()){

}

// Storable Interface Methods
void ConsultationRecord::getAttributesAndValues(QMap<QString, QVariant> * attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues->insert(QString("Reason"), QVariant(QString(*getReason())));
    attributesAndValues->insert(QString("DateAndTime"), QVariant(QDateTime(*getDateAndTime())));
    attributesAndValues->insert(QString("OHIPNumber"), QVariant(QString(*getOHIPNumber())));
    attributesAndValues->insert(QString("Diagnosis"), QVariant(QString(*getDiagnosis())));  
}

void ConsultationRecord::setAttributesAndValues(QMap<QString, QVariant> * attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString * r = new QString( attributesAndValues->value(QString("Reason")).toString());
    QDateTime * dat = new QDateTime(attributesAndValues->value(QString("DateAndTime")).toDateTime());
    QString * o = new QString( attributesAndValues->value(QString("OHIPNumber")).toString());
    QString * d = new QString( attributesAndValues->value(QString("Diagnosis")).toString());

    setReason(r);
    setDateAndTime(dat);
    setOHIPNumber(o);
    setDiagnosis(d);
}

QString ConsultationRecord::className() const{
    static QString className("ConsultationRecord");
    return className;
}

ConsultationRecord::~ConsultationRecord(){
    delete reason;
    delete dateAndTime;
    delete OHIPNumber;
    delete diagnosis;
}
