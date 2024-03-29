#ifndef STORABLEFACTORY_H
#define STORABLEFACTORY_H

#include "StorableInterface.h"

#include "ConsultationRecord.h"
#include "FollowUpRecord.h"
#include "PatientRecord.h"
#include "User.h"


class StorableFactory
{

public:


    static StorableFactory& GetFactory(){
        static StorableFactory currentFactory;
        return currentFactory;
    }


    StorableInterface * getInstance(QString * className);
    // Constructor
    StorableFactory();
    // Destructor
    ~StorableFactory();
};

#endif // STORABLEFACTORY_H
