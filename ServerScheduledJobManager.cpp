#include "ServerScheduledJobManager.h"

void ServerScheduledJobManager::scheduleJob(ServerScheduledJobInterface *job){
    jobs->append(job);
    QTimer * currentTimer = new QTimer();
    long interval = QTime::currentTime().msecsTo(job->timeOfDay());
    currentTimer->setInterval(interval);
    currentTimer->setSingleShot(true);
    currentTimer->start();
    timers->append(currentTimer);
    QObject::connect(currentTimer,SIGNAL(timeout()),this,SLOT(timerFired()));
}

void ServerScheduledJobManager::unscheduleJob(ServerScheduledJobInterface *job){
    for(int i = 0 ; i < jobs->length(); i++){
        if(jobs->at(i) == job){
            jobs->removeAt(i);
            delete job;
            QTimer * currentTimer = timers->at(i);
            timers->at(i)->stop();
            timers->removeAt(i);
            delete currentTimer;
        }
    }
}

void ServerScheduledJobManager::timerFired(){
    for(int i = 0; i < timers->length(); i++){
        if(!timers->at(i)->isActive()){ // Then it must have just fired

            QTime currentTime = QTime::currentTime();
            ServerScheduledJobInterface * currentJob = jobs->at(i);
            QTimer * currentTimer = timers->at(i);
            currentTime.addSecs(1);
            long interval = currentTime.msecsTo(jobs->at(i)->timeOfDay());
            currentJob->run();

            if(interval < 0){
                interval = 86400*1000 + interval;
            }

            currentTimer->setInterval(interval);

            currentTimer->start();

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
