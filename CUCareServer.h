#ifndef CUCARESERVER_H
#define CUCARESERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <CUCareDatabase.h>


#include <CUCareServerThread.h>

class CUCareServer: public QTcpServer
{
     Q_OBJECT
public:
    CUCareServer(QObject *parent = 0);
protected:
    CUCareDatabase * centralDatabase;
private slots:
    void incomingConnection(int socket);


};

#endif // CUCARESERVER_H
