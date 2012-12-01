#include "ServerScheduledJobManager.h"






void ServerScheduledJobManager::scheduleJob(ServerScheduledJobInterface *job){
    jobs.append(job);
    QTimer * currentTimer = new QTimer();
    long interval = QTime::currentTime().msecsTo(job->timeOfDay());
    currentTimer->setInterval(interval);
    timers.append(currentTimer);
    QObject::connect(currentTimer,SIGNAL())
}


ServerScheduledJobManager::ServerScheduledJobManager(){
    jobs = new QList<ServerScheduledJobInterface>();
    timers = new QList<QTimer>();
}

ServerScheduledJobManager::~ServerScheduledJobManager(){
    qDeleteAll(jobs);
    jobs.clear();
    delete jobs;
    qDeleteAll(timers);
    timers.clear();
    delete timers;
}
