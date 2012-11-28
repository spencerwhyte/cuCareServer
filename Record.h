/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef RECORD_H
#define RECORD_H


/*
  The purpose of the record class is to provide a
  superclass to which all other records inherit
  from. The specific ability that the record
  class provides is the unique identifier which
  is used to reference any given record
*/

#include "StorableInterface.h"

class Record : public StorableInterface
{
private:
    int id;
public:
    // Getters
    int getId();
    // Setters
    void setId(int newID);

    // Constructor
    Record();
    // Destructor
    ~Record();

    // Supports compliance with the StorableInterface
    virtual void getAttributesAndValues(QMap<QString, QVariant> * attributesAndValues) const;
    virtual void setAttributesAndValues(QMap<QString, QVariant> * attributesAndValues);
    virtual QString className() const;
    virtual QString getIdentifierKey() const;

};

#endif // RECORD_H
