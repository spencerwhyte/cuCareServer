/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include "User.h"


User::User(): username(new QString()), userType(Invalid){

}


QString * User::getUsername() const{
    return username;
}


User::UserType User::getUserType() const{
    return userType;
}


void User::setUsername( QString * u){
    delete username;
    username = u;
}


void User::setUserType(UserType type){
    userType = type;
}


// Storable Interface Methods
void User::getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const{
    Record::getAttributesAndValues(attributesAndValues);
    attributesAndValues.insert(QString("UserName"), QVariant(QString(*getUsername())));
    attributesAndValues.insert(QString("UserType"), QVariant(QString(stringForUserType())));
}

void User::setAttributesAndValues(QMap<QString, QVariant> & attributesAndValues){
    Record::setAttributesAndValues(attributesAndValues);
    QString * u = new QString( attributesAndValues.value(QString("Username")).toString());
    QString * type = new QString( attributesAndValues.value(QString("UserType")).toString());

    setUsername(u);
    setUserTypeForString(type);
    delete type;
}

QString User::className() const{
    static QString className("User");
    return className;
}


QString User::stringForUserType() const{
    if(getUserType() == Physician){
        static QString physician("Physician");
        return physician;
    }else if(getUserType() == MedicalPersonnel){
        static QString medicalPersonnel("MedicalPersonnel");
        return medicalPersonnel;
    }else if(getUserType() == Administrator){
        static QString administrator("Administrator");
        return administrator;
    }
    return QString("");
}

void User::setUserTypeForString(QString * u){

    if(u->compare(QString("Administrator")) == 0){
        userType =  Administrator;
    }else if(u->compare(QString("MedicalPersonnel")) == 0){
        userType = MedicalPersonnel;
    }else if(u->compare(QString("Physician")) == 0){
        userType = Physician;
    }else{
        userType = Invalid;
    }

}

User::~User(){
    delete username;
}
