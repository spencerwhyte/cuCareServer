#include "PatientAuditProcessManager.h"



/*

    This method gets called on the implementing object everytime
    the job is scheduled to run
        returns - Either 0 for success, or the appropriate error code

 */
int PatientAuditProcessManager::run(){

    QList<StorableInterface*> followUps;
    FollowUpRecord f;
    QList< QMap < QString, QVariant> > followUpsData;
    database->queryForObjects(f,followUpsData, false);
    for(int i = 0 ; i < followUpsData.length(); i++){
        QString className = f.className();
        FollowUpRecord * current = (FollowUpRecord *)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(followUpsData.at(i));
        followUps.append(current);
    }

    QList<StorableInterface*> consultations;
    QList< QMap < QString, QVariant> > consultationsData;
    ConsultationRecord c;
    database->queryForObjects(c,consultationsData, false);
    for(int i = 0 ;i <consultationsData.length(); i++){
        QString className = c.className();
        ConsultationRecord * current = (ConsultationRecord *)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(consultationsData.at(i));
        consultations.append(current);
    }

    QList<StorableInterface*> patients;
    PatientRecord p;
    QList< QMap < QString, QVariant> > patientsData;
    database->queryForObjects(p, patientsData, false);
    for(int i = 0 ; i < patientsData.length(); i++){
        QString className = p.className();
        PatientRecord * current = (PatientRecord*)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(patientsData.at(i));
        patients.append(current);
    }

    for(int i = 0 ; i < patients.length(); i++){

        PatientRecord * currentPatient = (PatientRecord *)patients.at(i);
        qDebug() << currentPatient->getOHIPNumber();
        for(int j = 0; j < consultations.length(); j++){
            ConsultationRecord * currentConsultation = (ConsultationRecord *)consultations.at(j);
            if(QString::compare(currentPatient->getOHIPNumber(), currentConsultation->getOHIPNumber()) == 0){ // This is a consultation for the current patient
                for(int k = 0 ; k < followUps.length(); k++){
                    FollowUpRecord * currentFollowUp = (FollowUpRecord *)followUps.at(k);
                    qDebug()<<currentFollowUp->getConsultationRecordId();
                    if(currentFollowUp->getConsultationRecordId() == currentConsultation->getId()){
                        bool shouldUpdate = false;
                        if(currentFollowUp->getStatus() == FollowUpRecord::OVERDUE && !currentPatient->getHasOverDueFollowUps()){
                            currentPatient->setHasOverDueFollowUps(true);
                            shouldUpdate = true;
                        }
                        if(currentFollowUp->getStatus() == FollowUpRecord::COMPLETE && !currentPatient->getHasCompletedFollowUps()){
                            currentPatient->setHasCompletedFollowUps(true);
                            shouldUpdate = true;
                        }
                        if(currentFollowUp->getStatus() == FollowUpRecord::PENDING && !currentPatient->getHasPendingFollowUps()){
                            currentPatient->setHasPendingFollowUps(true);
                            shouldUpdate = true;
                        }
                        if(shouldUpdate){
                           database->editObject(*currentPatient);
                        }
                    }
                }

            }
        }
    }
    qDeleteAll(patients);
    qDeleteAll(followUps);
    qDeleteAll(consultations);
}

/*
  This method allows the implementing object to specify whether or
  not this job should be run over and over again
        returns
                  true if we want the job to repeat itself after a
                  given amount of time

                  false if this job will be ran only once and then discarded
  */
 bool PatientAuditProcessManager::getRepeats(){
    return true;
}

/*
  This method allows the implementing object to specify the time of day
  at which the job should be run

       returns - The time of day at which this should be ran
*/
QTime PatientAuditProcessManager::timeOfDay(){
    return QTime(QTime::currentTime().addSecs(10));
}


PatientAuditProcessManager::PatientAuditProcessManager(CUCareDatabase * d) : time(new QTime(QTime::currentTime().addSecs(10))){
    database = d;
}

PatientAuditProcessManager::~PatientAuditProcessManager(){
        delete time;
}
