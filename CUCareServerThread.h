/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef CUCARESERVERTHREAD_H
#define CUCARESERVERTHREAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include "CUCareDatabase.h"


/*
    The purpose of this class is to allow the server to handle
    many concurrent sessions with many clients. Each time a new
    connection comes in, a CUCareServerThread is spawned to
    handle the request.
  */
class CUCareServerThread : public QThread
{
    Q_OBJECT
public:
    // Creates a CUCareServerThread with the database
    explicit CUCareServerThread(int s, CUCareDatabase * cd, QObject *parent = 0);
    // Begins running the thread
    void run();
    // Destructor
    ~CUCareServerThread();
 signals:
    // Tells us if there was an error with the current session
    // with the client
         void error(QTcpSocket::SocketError socketError);
    
public slots:
    
private:
    //  The socket connection to the current client
    int socket;
    // The database where all of the data for the current session
    // will be stored
    CUCareDatabase * centralDatabase;
};

#endif // CUCARESERVERTHREAD_H
