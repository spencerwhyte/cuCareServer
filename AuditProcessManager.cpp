#include "AuditProcessManager.h"



/*

    This method gets called on the implementing object everytime
    the job is scheduled to run
        returns - Either 0 for success, or the appropriate error code

 */
int AuditProcessManager::run(){
    qDebug() << "Begining audit process...";
    QList<StorableInterface*> followUps;
    FollowUpRecord f;
    QList< QMap < QString, QVariant> > followUpsData;
    database->queryForObjects(f,followUpsData, false);
    for(int i = 0 ; i < followUpsData.length(); i++){
        QString className = f.className();
        FollowUpRecord * current = (FollowUpRecord *)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(followUpsData.at(i));
        followUps.append(current);
        if(current->getStatus() == FollowUpRecord::PENDING && current->getDueDateTime().secsTo(QDateTime::currentDateTime()) > 0){
            current->setStatus(FollowUpRecord::OVERDUE);
            StorableInterface * object = (StorableInterface*)current;
           database->editObject(*object);
        }
    }
    qDebug() << "Audit process complete";
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


AuditProcessManager::AuditProcessManager(CUCareDatabase * d) : time(new QTime(QTime::currentTime().addSecs(10))){
    database = d;
}

AuditProcessManager::~AuditProcessManager(){
        delete time;
}
