#include "connection.h"


Connection::Connection(){}

bool Connection::createconnection()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("esprit");
    db.setUserName("system");
    db.setPassword("yosr");
    if(db.open())test=true;
    return test;

}


