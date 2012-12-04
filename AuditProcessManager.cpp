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
    getDatabase()->queryForObjects(f,followUpsData, false);
    for(int i = 0 ; i < followUpsData.length(); i++){
        QString className = f.className();
        FollowUpRecord * current = (FollowUpRecord *)StorableFactory::GetFactory().getInstance(&className);
        current->setAttributesAndValues(followUpsData.at(i));
        followUps.append(current);
        if(current->getStatus() == FollowUpRecord::PENDING && current->getDueDateTime().secsTo(QDateTime::currentDateTime()) > 0){
            current->setStatus(FollowUpRecord::OVERDUE);
            StorableInterface * object = (StorableInterface*)current;
            getDatabase()->editObject(*object);
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
    return QTime(*getTime());
}

/*
  Sets the time of day when the audit process should run.
  */
void AuditProcessManager::setTimeOfDay(QTime newTime){
    delete time;
    time = new QTime(newTime);
}


AuditProcessManager::AuditProcessManager(CUCareDatabase * d) :
    time(new QTime(QTime::currentTime().addSecs(10))),
    database(d),
    settings(new QSettings(QString("./AuditFollowUps.config"), QSettings::IniFormat))
    {

    int h = getSettings()->value(QString("Hour"),QVariant(QTime::currentTime().hour())).toInt();
    int m = getSettings()->value(QString("Minute"),QVariant(QTime::currentTime().minute())).toInt();
    int s = getSettings()->value(QString("Second"),QVariant(QTime::currentTime().second())).toInt();
    time->setHMS(h,m,s);
    if(getSettings()->allKeys().length() ==0){
        getSettings()->setValue(QString("Hour"), QVariant(h));
        getSettings()->setValue(QString("Minute"), QVariant(m));
        getSettings()->setValue(QString("Second"), QVariant(s));
    }
}

QTime * AuditProcessManager::getTime(){
    return time;
}

CUCareDatabase * AuditProcessManager::getDatabase(){
    return database;
}

QSettings * AuditProcessManager::getSettings(){
    return settings;
}

AuditProcessManager::~AuditProcessManager(){
        delete time;
        delete settings;
}
