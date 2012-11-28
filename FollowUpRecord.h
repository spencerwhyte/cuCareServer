/*
  By: Spencer Whyte
  # 100817664
  Carleton University
*/

#ifndef FOLLOWUPRECORD_H
#define FOLLOWUPRECORD_H



#include <QDateTime>
#include "Record.h"

/*
    The purpose of the FollowUpRecord class is to
    encapsulate all of the inforamtion pertaining
    to an individual FollowUpRecord.
  */

class FollowUpRecord : public Record
{
public:
    typedef enum FollowUpRecordStatus{
        PENDING,
        OVERDUE,
        COMPLETE,
        INVALID
    }FollowUpRecordStatus;
private:
    // Private attributes
    FollowUpRecordStatus status;
    QDateTime * dueDateTime;
    QString * details;
public:
    // Setters
    void setStatus(FollowUpRecordStatus  status);
    void setDueDateTime(QDateTime * dueDateTime);
    void setDetails(QString * details);
    void setStatusForString(QString * status);
    // Getters

    FollowUpRecordStatus getStatus() const;
    QDateTime * getDueDateTime() const;
    QString * getDetails() const;
    QString & getStatusString() const;

    // Storable Interface Methods
    virtual void getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const;
    virtual void setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues);
    virtual QString className() const;

    // Constructor / Destructor
    FollowUpRecord();
    ~FollowUpRecord();
};

#endif // FOLLOWUPRECORD_H
