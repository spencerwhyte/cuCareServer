#ifndef CUCARESERVERTHREAD_H
#define CUCARESERVERTHREAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <CUCareDatabase.h>
#include <HTTPRequest.h>

class CUCareServerThread : public QThread
{
    Q_OBJECT
public:
    explicit CUCareServerThread(int s, CUCareDatabase * cd, QObject *parent = 0);
    
    void run();

 signals:
         void error(QTcpSocket::SocketError socketError);
    
public slots:
    

private:
         int socket;
         CUCareDatabase * centralDatabase;
};

#endif // CUCARESERVERTHREAD_H
