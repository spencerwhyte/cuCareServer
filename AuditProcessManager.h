#ifndef AUDITPROCESSMANAGER_H
#define AUDITPROCESSMANAGER_H

#include "ServerScheduledJobInterface.h"
#include <QDebug>
#include "CUCareDatabase.h"
#include "FollowUpRecord.h"
#include "PatientRecord.h"
#include "StorableFactory.h"

class AuditProcessManager : public  ServerScheduledJobInterface
{
    QTime * time;
    CUCareDatabase * database;
    QSettings * settings;

    QTime * getTime();
    CUCareDatabase * getDatabase();
    QSettings * getSettings();
public:
    /*
  Sets the time of day when the audit process should run.
  */
    void setTimeOfDay(QTime newTime);

    /* This method gets called on the implementing object everytime
    the job is scheduled to run
        returns - Either 0 for success, or the appropriate error code
 */
    int run();
    /*
  This method allows the implementing object to specify whether or
  not this job should be run over and over again
        returns
                  true if we want the job to repeat itself after a
                  given amount of time

                  false if this job will be ran only once and then discarded
  */
     bool getRepeats();
    /*
  This method allows the implementing object to specify the time of day
  at which the job should be run

       returns - The time of day at which this should be ran
*/
     QTime timeOfDay();

    AuditProcessManager(CUCareDatabase * d);
    ~AuditProcessManager();
};

#endif // AUDITPROCESSMANAGER_H
