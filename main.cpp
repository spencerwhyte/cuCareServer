#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "CUCareServer.h"

/*
void testAddUser(){
    CUCareDatabase * database = new CUCareDatabase();
    User u(new QString("spencerwhyte"));
    u.setUserType(User::Physician);
    if (database->addUser(u)){
         qDebug()<< "Added user successfully";
    }else{
        qDebug() << "Failed to add user";
    }

    if(database->authenticateUser(u)){
        qDebug() << "AnD the user authenticated";
    }else{
        qDebug() << "AND THE USER did not authenticate";
    }

}
*/
void testServer(){
    CUCareServer * server= new CUCareServer();
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));


   // testAddUser();

    testServer();

    return app->exec();
}


