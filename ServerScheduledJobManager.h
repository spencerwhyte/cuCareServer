#ifndef SERVERSCHEDULEDJOBMANAGER_H
#define SERVERSCHEDULEDJOBMANAGER_H

#include "ServerScheduledJobInterface.h"
#include <QList>
#include <QObject>
#include <QTimer>

class ServerScheduledJobManager : public QObject
{
    Q_OBJECT
    QList<ServerScheduledJobInterface *> jobs;
    QList<QTimer *> timers;

public:
    static ServerScheduledJobManager& GetManager(){
        static ServerScheduledJobManager currentManger;
        return currentManger;
    }

    void scheduleJob(ServerScheduledJobInterface *job);


private:


    ServerScheduledJobManager();        
    ServerScheduledJobManager(ServerScheduledJobManager const&);
    void operator=(ServerScheduledJobManager const&);

};

#endif // SERVERSCHEDULEDJOBMANAGER_H
