/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef CONSULTATIONRECORD_H
#define CONSULTATIONRECORD_H

#include "Record.h"
#include <QDateTime>


/*
  The purpose of the ConsultationRecord class is to
  encapsulate all of the information having to do
  with an individual ConsulatationRecord. The class
  also implements the StorableInterface which allows
  it's objects to be both sent over the network and
  stored in the database.
*/

class ConsultationRecord : Record
{
private:
    // Private Attributes
   QDateTime * dateAndTime;
   QString * reason;
   QString * OHIPNumber;
   QString * diagnosis;


public:
   // Getters
   QDateTime * getDateAndTime() const;
   QString * getReason() const;
   QString * getOHIPNumber() const;
   QString * getDiagnosis() const;


   // Setters
   void setDateAndTime(QDateTime * newDateAndTime);
   void setReason(QString* newReason);
   void setOHIPNumber(QString* newOHIPNumber);
   void setDiagnosis(QString* diagnosis);

   // Storable Interface Methods
   virtual void getAttributesAndValues(QMap<QString, QVariant> * attributesAndValues) const;
   virtual void setAttributesAndValues(QMap<QString, QVariant> * attributesAndValues);
   virtual QString className() const;

   // Constructor and destructor
    ConsultationRecord();
    ~ConsultationRecord();
};

#endif // CONSULTATIONRECORD_H
