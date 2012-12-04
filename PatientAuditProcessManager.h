#ifndef PATIENTAUDITPROCESSMANAGER_H
#define PATIENTAUDITPROCESSMANAGER_H
#include "ServerScheduledJobInterface.h"
#include <QDebug>
#include "CUCareDatabase.h"
#include "FollowUpRecord.h"
#include "PatientRecord.h"
#include "StorableFactory.h"

class PatientAuditProcessManager : public ServerScheduledJobInterface
{
    QTime * time;
    CUCareDatabase * database;
public:
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

    PatientAuditProcessManager(CUCareDatabase * d);
    ~PatientAuditProcessManager();
};

#endif // PATIENTAUDITPROCESSMANAGER_H
