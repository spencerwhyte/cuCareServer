/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */
#ifndef CUCAREDATABASE_H
#define CUCAREDATABASE_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QtCore/QCoreApplication>
#include <QtSql>
#include <QtSql/QSqlQuery>
#include "PatientRecord.h"
#include "User.h"
#include "ConsultationRecord.h"
#include <QList>
#include <QMap>
#include "StorableInterface.h"
#include <QVariant>


/*
  The purpose of CUCareDatabase class is to manage
  storage, modification and querying of any storable
  objects.This database is backed by SQLite database.

  */
class CUCareDatabase : public QObject
{
    Q_OBJECT
public:
    // The database that will be used to store all of
    // it's objects
    QSqlDatabase  db;
    /*
        Adds an object to the database

                object - The object to be added
      */
    int addObject(StorableInterface & object);
    /*
        Updates the information pertaining to a particular object in the database

                object - The object whose information is to be updated
      */
    int editObject(StorableInterface & object);
    /*// Adds the object to the database
        Removes the given object from the database

                object - The object to be removed
      */
    int removeObject(StorableInterface & object);
    /*
        Query's for all objects similar to the specified object

                object - The object to be queried for

                queryResults - Output parameter for the results
                of the query being requested

                equality - Whether or not we should check for exact equality
      */
    int queryForObjects(StorableInterface & object,  QList< QMap < QString, QVariant> > & queryResults, bool equality);
    /*
        Convienence method for determining if the database has any data in it yet.

            returns - True of the database is empty
     */
    bool isEmpty();

    // Destructor
    ~CUCareDatabase();
    // Constructs the CUCareDatabase, giving it the name of the repository
    CUCareDatabase(QString * name, QObject *parent);
private:
    // Adds a new table to the database to store objects of the firstObejct type.
    bool initializeTableWithSchemaOfObject(StorableInterface & firstObject);
    // Checks to see if a database table for a given object is initialized yet
    bool isDatabaseTableInitialized(QString className);
    // Creates the database with the specified name
    bool createDatabase(QString * databaseName);
    // Executes the given query on the database
    QSqlQuery executeQuery(const QString& sql);

};

#endif // CUCAREDATABASE_H
