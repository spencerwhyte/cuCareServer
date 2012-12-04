/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H
#include "Record.h"

/*
  The purpose of the PatientRecord class is to encapsulate
  all of the information that is pertinant to one
  patient. The PatientRecord class also implements
  the StorableInterface so that this object can be
  both sent over the network and stored in the
  database.
  */
class PatientRecord : public Record
{
private:
    // Private Attributes
    QString * name;
    QString * phoneNumber;
    QString * OHIPNumber;
    QString * primaryPhysician;

    bool hasOverDueFollowUps;
    bool hasPendingFollowUps;
    bool hasCompletedFollowUps;
public:

    // Getters
    QString getName() const;
    QString getPhoneNumber() const;
    QString getOHIPNumber() const;
    QString getPrimaryPhysician() const;

    bool getHasOverDueFollowUps()const;
    bool getHasPendingFollowUps()const;
    bool getHasCompletedFollowUps()const;

    bool booleanForString(QString string)const;
    QString stringForBoolean(bool value) const;


    // Setters
    void setName(QString newName);
    void setPhoneNumber(QString newPhoneNumber);
    void setOHIPNumber(QString newOhipNumber);
    void setPrimaryPhysician(QString newPrimaryPhysician) ;
    void setHasOverDueFollowUps(bool newValue);
    void setHasPendingFollowUps(bool newValue);
    void setHasCompletedFollowUps(bool newValue);

    // Storable Interface Methods
    virtual void getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const;
    virtual void setAttributesAndValues(const QMap<QString, QVariant> & attributesAndValues);
    virtual QString className() const;

    // Constructor and destructor
    PatientRecord();
    PatientRecord(QString &n,QString&p, QString&o, QString &pp);
    ~PatientRecord();
};

#endif // PATIENTRECORD_H
