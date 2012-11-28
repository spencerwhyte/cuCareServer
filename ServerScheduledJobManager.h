#ifndef SERVERSCHEDULEDJOBMANAGER_H
#define SERVERSCHEDULEDJOBMANAGER_H

class ServerScheduledJobManager
{
public:
    ServerScheduledJobManager& getManager(){
        static ServerScheduledJobManager currentManger;
        return currentManger;
    }


private:
    ServerScheduledJobManager();        
    ServerScheduledJobManager(ServerScheduledJobManager const&);
    void operator=(ServerScheduledJobManager const&);

};

#endif // SERVERSCHEDULEDJOBMANAGER_H
