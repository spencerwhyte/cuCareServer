#include "AuditProcessManager.h"



/* This method gets called on the implementing object everytime
    the job is scheduled to run
        returns - Either 0 for success, or the appropriate error code
 */
int AuditProcessManager::run(){
    qDebug() << "AUDIT FOLLOW UPS";
    QString dbName("cuCare");
    CUCareDatabase database(&dbName, NULL);

    QList<StorableInterface*> followUps;
    FollowUpRecord f;
    QList< QMap < QString, QVariant> > followUpsData;
    //queryForObjects(StorableInterface & object,  QList< QMap < QString, QVariant> > & queryResults, bool equality);
    database.queryForObjects(f,followUpsData, false);

    for(int i = 0 ; i < followUpsData.length(); i++){
        QString className = f.className();
        FollowUpRecord * current = (FollowUpRecord *)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(followUpsData.at(i));
        followUps.append(current);
        if(current->getStatus() == FollowUpRecord::PENDING && current->getDueDateTime().msecsTo(QDateTime::currentDateTime()) < 0){
           current->setStatus(FollowUpRecord::OVERDUE);
           database.editObject(f);
        }
    }

    QList<StorableInterface*> consultations;
    QList< QMap < QString, QVariant> > consultationsData;
    ConsultationRecord c;
    database.queryForObjects(c,consultationsData, false);
    for(int i = 0 ;i <consultationsData.length(); i++){
        QString className = c.className();
        ConsultationRecord * current = (ConsultationRecord *)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(consultationsData.at(i));
        //consultations.append(current);
    }


    QList<StorableInterface*> patients;
    PatientRecord p;
    QList< QMap < QString, QVariant> > patientsData;
    database.queryForObjects(p, patientsData, false);

    for(int i = 0 ; i < patients.length(); i++){
        QString className = p.className();
        //PatientRecord * current = StorableFactory::GetFactory().getInstance(&className);
        //current->setAttributesAndValues(patientsData.at(i));-
        //patientsData.append(current);
    }

    for(int i = 0 ; i < patients.length(); i++){
        PatientRecord * currentPatient = (PatientRecord *)patients.at(i);
        for(int j = 0; j < consultations.length(); j++){
            ConsultationRecord * currentConsultation = (ConsultationRecord *)consultations.at(i);
            if(currentPatient->getOHIPNumber() == currentConsultation->getOHIPNumber()){ // This is a consultation for the current patient
                for(int k = 0 ; k < followUps.length(); k++){
                    FollowUpRecord * currentFollowUp = (FollowUpRecord *)followUps.at(i);
                    if(currentFollowUp->getConsultationRecordId() == currentConsultation->getId()){
                        if(currentFollowUp->getStatus() == FollowUpRecord::OVERDUE){
                            currentPatient->setHasOverDueFollowUps(true);
                        }
                        if(currentFollowUp->getStatus() == FollowUpRecord::COMPLETE){
                            currentPatient->setHasCompletedFollowUps(true);
                        }
                        if(currentFollowUp->getStatus() == FollowUpRecord::PENDING){
                            currentPatient->setHasPendingFollowUps(true);
                        }
                    }

                }

            }

        }
    }


}

/*
  This method allows the implementing object to specify whether or
  not this job should be run over and over again
        returns
                  true if we want the job to repeat itself after a
                  given amount of time

                  false if this job will be ran only once and then discarded
  */
 bool AuditProcessManager::getRepeats(){
    return true;
}

/*
  This method allows the implementing object to specify the time of day
  at which the job should be run

       returns - The time of day at which this should be ran
*/
QTime AuditProcessManager::timeOfDay(){
    return QTime(*time);
}

/*
  Sets the time of day when the audit process should run.
  */
void AuditProcessManager::setTimeOfDay(QTime newTime){
    delete time;
    time = new QTime(newTime);
}


AuditProcessManager::AuditProcessManager() : time(new QTime()){

}

AuditProcessManager::~AuditProcessManager(){
        delete time;
}
