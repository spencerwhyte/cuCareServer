#include "ServerScheduledJobManager.h"



void ServerScheduledJobManager::scheduleJob(ServerScheduledJobInterface *job){

    jobs->append(job);

    QTimer * currentTimer = new QTimer();
    long interval = QTime::currentTime().msecsTo(job->timeOfDay());
    currentTimer->setInterval(interval);
    currentTimer->setSingleShot(true);
    timers->append(currentTimer);

    QObject::connect(currentTimer,SIGNAL(timeout()),this,SLOT(timerFired()));

}

void ServerScheduledJobManager::unscheduleJob(ServerScheduledJobInterface *job){

}

void ServerScheduledJobManager::timerFired(){

    for(int i = 0; i < timers->length(); i++){
        if(!timers->at(i)->isActive()){ // Then it must have just fired
            QTimer * currentTimer = timers->at(i);
            QTime currentTime = QTime::currentTime();
            currentTime.addSecs(1);
            long interval = currentTime.msecsTo(jobs->at(i)->timeOfDay());
            if(interval < 0){
                interval = 86400*1000 + interval;
            }
            currentTimer->setInterval(interval);

        }
    }

}

ServerScheduledJobManager::ServerScheduledJobManager(){
    jobs = new QList<ServerScheduledJobInterface *>;
    timers = new QList<QTimer *>;
}

ServerScheduledJobManager::~ServerScheduledJobManager(){
    qDeleteAll(*jobs);
    jobs->clear();
    delete jobs;
    qDeleteAll(*timers);
    timers->clear();
    delete timers;
}
