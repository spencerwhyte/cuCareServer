#include "FollowUpRecord.h"

// Setters

void FollowUpRecord::setStatusForString(QString s){
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

void FollowUpRecord::setDueDateTime(QDateTime  d){
    delete dueDateTime;
    dueDateTime = new QDateTime(d);
}


void FollowUpRecord::setDetails(QString  d){
    delete details;
    details = new QString(d);
}

void FollowUpRecord::setConsultationRecordId(int newID){
    consultationRecordId = newID;
}

// Getters




QString FollowUpRecord::getStatusString() const{
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

QDateTime FollowUpRecord::getDueDateTime() const{
    return *dueDateTime;
}

QString FollowUpRecord::getDetails() const{
    return *details;
}

int FollowUpRecord::getConsultationRecordId()const{
    return consultationRecordId;
}

// Storable Interface Methods
void FollowUpRecord::getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues.insert(QString("Status"), QVariant(getStatusString()));
    attributesAndValues.insert(QString("DueDateAndTime"), QVariant(QDateTime(getDueDateTime())));
    attributesAndValues.insert(QString("Details"), QVariant(QString(getDetails())));
    attributesAndValues.insert(QString("ConsultationRecordID"), QVariant(getConsultationRecordId()));
}

void FollowUpRecord::setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString  s = attributesAndValues.value(QString("Status")).toString();
    QDateTime  ddat = attributesAndValues.value(QString("DueDateAndTime")).toDateTime();
    QString  d = attributesAndValues.value(QString("Details")).toString();
    int c = attributesAndValues.value(QString("ConsultationRecordID")).toInt();

    setStatusForString(s);
    setDueDateTime(ddat);
    setDetails(d);
    setConsultationRecordId(c);
}

QString FollowUpRecord:: className() const{
    static QString className("FollowUpRecord");
    return className;
}

// Constructor / Destructor
FollowUpRecord::FollowUpRecord() : status(INVALID), dueDateTime(new QDateTime()), details(new QString()), consultationRecordId(-1){

}

FollowUpRecord::~FollowUpRecord(){
    delete dueDateTime;
    delete details;
}
