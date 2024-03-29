/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef SERVERSCHEDULEDJOBINTERFACE_H
#define SERVERSCHEDULEDJOBINTERFACE_H

#include <QTime>

/*
    This is the ServerScheduledJobInterface which is responsible for
    providing an interface for jobs that are to be scheduled in the
    ServerScheduledJobManager to provide more information to the
    manager such as the time of next run and most importantly an
    outlet method to be called when it is actually time to run the
    job.
*/

class ServerScheduledJobInterface{
    public:

    /* This method gets called on the implementing object everytime
        the job is scheduled to run
            returns - Either 0 for success, or the appropriate error code
     */
    virtual int run() = 0;

    /*
      This method allows the implementing object to specify whether or
      not this job should be run over and over again
            returns
                      true if we want the job to repeat itself after a
                      given amount of time

                      false if this job will be ran only once and then discarded
      */
    virtual bool getRepeats() = 0;

    /*
      This method allows the implementing object to specify the time of day
      at which the job should be run

           returns - The time of day at which this should be ran
    */
    virtual QTime timeOfDay() = 0;

    ~ServerScheduledJobInterface() {};

};

#endif // SERVERSCHEDULEDJOBINTERFACE_H
