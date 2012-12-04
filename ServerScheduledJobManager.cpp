#include "ServerScheduledJobManager.h"

void ServerScheduledJobManager::scheduleJob(ServerScheduledJobInterface *job){
    getJobs()->append(job);
    QTimer * currentTimer = new QTimer();
    long interval = QTime::currentTime().msecsTo(job->timeOfDay());
    if(interval < 0){
        interval = 86400*1000 + interval;
    }
    currentTimer->setInterval(interval);
    currentTimer->setSingleShot(true);
    currentTimer->start();
    timers->append(currentTimer);
    QObject::connect(currentTimer,SIGNAL(timeout()),this,SLOT(timerFired()));
}

QList<ServerScheduledJobInterface *> * ServerScheduledJobManager::getJobs(){
    return jobs;
}

QList<QTimer *> * ServerScheduledJobManager::getTimers(){
    return timers;
}

void ServerScheduledJobManager::unscheduleJob(ServerScheduledJobInterface *job){
    for(int i = 0 ; i < getJobs()->length(); i++){
        if(getJobs()->at(i) == job){
            getJobs()->removeAt(i);
            delete job;
            QTimer * currentTimer = getTimers()->at(i);
            getTimers()->at(i)->stop();
            getTimers()->removeAt(i);
            delete currentTimer;
        }
    }
}

void ServerScheduledJobManager::timerFired(){
    for(int i = 0; i < getTimers()->length(); i++){
        if(!getTimers()->at(i)->isActive()){ // Then it must have just fired

            QTime currentTime = QTime::currentTime();
            ServerScheduledJobInterface * currentJob = getJobs()->at(i);
            QTimer * currentTimer = getTimers()->at(i);
            currentTime.addSecs(1);
            long interval = currentTime.msecsTo(getJobs()->at(i)->timeOfDay());
            currentJob->run();

            if(interval < 0){
                interval = 86400*1000 + interval;
            }

            currentTimer->setInterval(interval);

            currentTimer->start();

        }
    }

}

ServerScheduledJobManager::ServerScheduledJobManager() :
    jobs (new QList<ServerScheduledJobInterface *>),
    timers(new QList<QTimer *>){
}

ServerScheduledJobManager::~ServerScheduledJobManager(){
    qDeleteAll(*jobs);
    jobs->clear();
    delete jobs;
    qDeleteAll(*timers);
    timers->clear();
    delete timers;
}
