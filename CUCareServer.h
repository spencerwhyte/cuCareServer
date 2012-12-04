/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef CUCARESERVER_H
#define CUCARESERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <CUCareDatabase.h>
#include <CUCareServerThread.h>
#include <AuditProcessManager.h>
#include <ServerScheduledJobManager.h>
#include <PatientAuditProcessManager.h>

/*
  The purpose of the CUCareServer object is to handle incoming TCP
  connections for the server and spawn the appropriate threads that
  are used to handle each request
  */
class CUCareServer : public QTcpServer
{
     Q_OBJECT
     ServerScheduledJobManager * jobManager;
public:
    // Constructor
    CUCareServer(QObject *parent = 0);
    ~CUCareServer();
protected:
    // The database that will be used to store all of the information
    // for this server
    CUCareDatabase * centralDatabase;
private slots:
    // Handles an incoming TCP connection
    void incomingConnection(int socket);

private:
    void populateServerTest(CUCareDatabase *database);


};

#endif // CUCARESERVER_H
