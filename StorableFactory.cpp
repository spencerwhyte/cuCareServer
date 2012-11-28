#include "StorableFactory.h"



StorableInterface& getInstance(QString * className){
    if(className->compare(*className, QString("ConsultationRecord"), Qt::CaseInsensitive) == 0){
        return ConsultationRecord();
    }else if(className->compare(*className, QString("FollowUpRecord"), Qt::CaseInsensitive) == 0){
        return FollowUpRecord();
    }else if(className->compare(*className, QString("PatientRecord"), Qt::CaseInsensitive) == 0){
        return PatientRecord();
    }else if(className->compare(*className, QString("User"), Qt::CaseInsensitive) == 0){
        return User();
    }
    qDebug()<< "An error occured in StorableFactory.cpp when trying to construct a storable object from the string " << *className;
    return NULL;
}


// Constructor
StorableFactory(){

}

// Destructor
~StorableFactory(){

}
