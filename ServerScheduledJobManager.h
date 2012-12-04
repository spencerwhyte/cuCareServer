/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERSCHEDULEDJOBMANAGER_H
#define SERVERSCHEDULEDJOBMANAGER_H

#include "ServerScheduledJobInterface.h"
#include <QList>
#include <QObject>
#include <QTimer>
#include <QDebug>


/*
  The purpose of the ServerScheduledJobManager is to allow
  other components of the system to schedule other jobs that
  need to be run at particular times.

  */
class ServerScheduledJobManager : public QObject
{
    Q_OBJECT
    QList<ServerScheduledJobInterface *> * jobs;
    QList<QTimer *> * timers;

    QList<ServerScheduledJobInterface *> * getJobs();
    QList<QTimer *> * getTimers();

public:

    /*
      Schedules a job to be run. The job implements the
      ServerScheduledJobInterface and specifies information
      about itself through that interface.

        job - The job to be scheduled.
      */
    void scheduleJob(ServerScheduledJobInterface *job);

    /*
      Unschedules a job from the manager. The job will be delted from memory
      and will never run again.

        job - The job to be unscheduled
      */
    void unscheduleJob(ServerScheduledJobInterface *job);


    ServerScheduledJobManager();
    ~ServerScheduledJobManager();

private slots:
    void timerFired();

};

#endif // SERVERSCHEDULEDJOBMANAGER_H
