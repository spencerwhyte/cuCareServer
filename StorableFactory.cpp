#include "StorableFactory.h"



StorableInterface * StorableFactory::getInstance(QString * className){
    if(className->compare(*className, QString("ConsultationRecord"), Qt::CaseInsensitive) == 0){
        return new ConsultationRecord();
    }else if(className->compare(*className, QString("FollowUpRecord"), Qt::CaseInsensitive) == 0){
        return new FollowUpRecord();
    }else if(className->compare(*className, QString("PatientRecord"), Qt::CaseInsensitive) == 0){
        return new PatientRecord();
    }else if(className->compare(*className, QString("User"), Qt::CaseInsensitive) == 0){
        return new User();
    }
    return NULL;
}


// Constructor
StorableFactory::StorableFactory(){

}

// Destructor
StorableFactory::~StorableFactory(){

}
