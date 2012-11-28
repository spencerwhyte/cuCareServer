#include "FollowUpRecord.h"

// Setters
void FollowUpRecord::setStatus(FollowUpRecordStatus  s){
    delete status;
    status = s;
}

void FollowUpRecord::setDueDateTime(QDateTime * d){
    delete dueDateTime;
    dueDateTime = d;
}

void FollowUpRecord::setDetails(QString * d){
    delete details;
    details = d;
}

// Getters

FollowUpRecord::FollowUpRecordStatus FollowUpRecord::getStatus() const{
    return status;
}

QDateTime * FollowUpRecord::getDueDateTime() const{
    return dueDateTime;
}

QString * FollowUpRecord::getDetails() const{
    return details;
}

// Storable Interface Methods
void FollowUpRecord::getAttributesAndValues(QMap<QString, QVariant> * attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues->insert(QString("Status"), QVariant(QString(*getStatus())));
    attributesAndValues->insert(QString("DueDateAndTime"), QVariant(QDateTime(*getDueDateTime())));
    attributesAndValues->insert(QString("Details"), QVariant(QString(*getDetails())));
}

void FollowUpRecord::setAttributesAndValues(QMap<QString, QVariant> * attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString * s = new QString( attributesAndValues->value(QString("Status")).toString());
    QDateTime * ddat = new QDateTime(attributesAndValues->value(QString("DueDateAndTime")).toDateTime());
    QString * d = new QString( attributesAndValues->value(QString("Details")).toString());

    setStatus(s);
    setDueDateTime(ddat);
    setDetails(d);
}

FollowUpRecord::QString className() const{
    static QString className("FollowUpRecord");
    return className;
}

// Constructor / Destructor
FollowUpRecord::FollowUpRecord() : status(new QString()), dueDateTime(new QDateTime()), details(new QString()){

}

FollowUpRecord::~FollowUpRecord(){
    delete status;
    delete dueDateTime;
    delete details;
}
