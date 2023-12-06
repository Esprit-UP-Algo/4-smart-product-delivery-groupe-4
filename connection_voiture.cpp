#include "connection_voiture.h"
#include<QDebug>
#include<QDebug>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Farouk");//inserer nom de l'utilisateur
db.setPassword("Tunisie3012");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;



    return  test;
}
