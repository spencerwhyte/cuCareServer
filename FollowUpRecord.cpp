#include "FollowUpRecord.h"

// Setters

void FollowUpRecord::setStatusForString(QString * s){
    if(QString::compare(QString("PENDING"),s) == 0){
        setStatus(PENDING);
    }else if(QString::compare(QString("OVERDUE"),s) == 0){
        setStatus(OVERDUE);
    }else if(QString::compare(QString("COMPLETE"),s) == 0){
        setStatus(COMPLETE);
    }
    setStatus(INVALID);
}

void FollowUpRecord::setStatus(FollowUpRecordStatus  s){
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




QString & FollowUpRecord::getStatusString() const{
    if(getStatus() == COMPLETE){
        static QString complete("COMPLETE");
        return complete;
    }else if(getStatus() == PENDING){
        static QString complete("COMPLETE");
        return complete;
    }else if(getStatus() == OVERDUE){
        static QString complete("COMPLETE");
        return complete;
    }
    static QString invalid("INVALID");
    return invalid;
}

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
void FollowUpRecord::getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues.insert(QString("Status"), QVariant(getStatusString()));
    attributesAndValues.insert(QString("DueDateAndTime"), QVariant(QDateTime(*getDueDateTime())));
    attributesAndValues.insert(QString("Details"), QVariant(QString(*getDetails())));
}

void FollowUpRecord::setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString * s = new QString( attributesAndValues.value(QString("Status")).toString());
    QDateTime * ddat = new QDateTime(attributesAndValues.value(QString("DueDateAndTime")).toDateTime());
    QString * d = new QString( attributesAndValues.value(QString("Details")).toString());

    setStatusForString(s);
    delete s;
    setDueDateTime(ddat);
    setDetails(d);
}

QString FollowUpRecord:: className() const{
    static QString className("FollowUpRecord");
    return className;
}

// Constructor / Destructor
FollowUpRecord::FollowUpRecord() : status(INVALID), dueDateTime(new QDateTime()), details(new QString()){

}

FollowUpRecord::~FollowUpRecord(){
    delete dueDateTime;
    delete details;
}
