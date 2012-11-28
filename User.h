/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef USER_H
#define USER_H

#include <QObject>
#include <QtXml>
#include <Record.h>

/*
  The purpose of the user class is to encapsulate
  all of the information and functionality having
  to do with an individual user.
  */

class User : public Record
{
public:
    typedef enum UserType{
           Administrator,
           MedicalPersonnel,
           Physician,
           Invalid
    }UserType;

   // Getters
   QString * getUsername() const;
   UserType getUserType() const;

   // Utility getter
   QString stringForUserType() const;

   // Setters
   void setUsername(QString *username);
   void setUserType(UserType type);
   // Utility setter
   void setUserTypeForString(QString * userType);

   //Constructor
   User();
   // Destructor
   ~User();

   // Storable Interface Methods
   virtual void getAttributesAndValues(QMap<QString, QVariant> * attributesAndValues) const;
   virtual void setAttributesAndValues(QMap<QString, QVariant> * attributesAndValues);
   virtual QString className() const;
    
private:
   UserType userType;
   QString * username;
};

#endif // USER_H
