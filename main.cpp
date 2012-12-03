/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "CUCareServer.h"
#include <QTime>


void testServer(){
    CUCareServer * server= new CUCareServer();
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    testServer();

    return app->exec();
}


