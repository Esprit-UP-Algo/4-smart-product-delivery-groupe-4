#include "livraisons.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>
#include<iostream>
using namespace std;


Livraisons::Livraisons()
{
NUMLIV=0; ADRESSELIV=" "; STATUTLIV=" "; DATELIV=" ";
}
Livraisons::Livraisons(int NUMLIV,QString ADRESSELIV,QString STATUTLIV,QString DATELIV)
{this->NUMLIV=NUMLIV; this->STATUTLIV=STATUTLIV; this->ADRESSELIV=ADRESSELIV; this->DATELIV=DATELIV; }
int Livraisons::getNUMLIV(){return NUMLIV;}
QString Livraisons::getADRESSELIV(){return ADRESSELIV;}
QString Livraisons::getSTATUTLIV(){return STATUTLIV;}
QString Livraisons::getDATELIV(){return DATELIV;}
void Livraisons::setNUMLIV(int NUMLIV){this->NUMLIV=NUMLIV;}
void Livraisons::setADRESSELIV(QString ADRESSELIV){this->ADRESSELIV=ADRESSELIV;}
void Livraisons::setSTATUTLIV(QString STATUTLIV){this->STATUTLIV=STATUTLIV;}
void Livraisons::setDATELIV(QString DATELIV){this->DATELIV=DATELIV;}


bool Livraisons::ajouter()
{
    QSqlQuery query;

    QString res = QString::number(NUMLIV);
          query.prepare("insert into LIVRAISONS (NUMLIV ,STATUTLIV, DATELIV, ADRESSELIV) "
                        "values (:NUMLIV, :STATUTLIV, :DATELIV, :ADRESSELIV)");
          query.bindValue(":NUMLIV", res);
          query.bindValue(":STATUTLIV", STATUTLIV);
          query.bindValue(":DATELIV", DATELIV);
          query.bindValue(":ADRESSELIV", ADRESSELIV);





return  query.exec();
}
bool Livraisons::supprimer(int NUMLIV)
{
    QSqlQuery query;
    QString num_string= QString::number(NUMLIV);
          query.prepare("Delete from LIVRAISONS where NUMLIV= :NUMLIV");
          query.bindValue(":NUMLIV", NUMLIV);

return  query.exec();
}
QSqlQueryModel* Livraisons::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("select * from LIVRAISONS");
/*model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMLIV"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("STATUTLIV"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATELIV"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSELIV"));*/


    return model;
}
bool Livraisons::modifier()
{
    QSqlQuery query;

    QString res = QString::number(NUMLIV);
          query.prepare("UPDATE LIVRAISONS SET ADRESSELIV =:ADRESSELIV , STATUTLIV = :STATUTLIV, DATELIV = :DATELIV WHERE NUMLIV = :NUMLIV ");
          query.bindValue(":NUMLIV", res);
          query.bindValue(":ADRESSELIV", ADRESSELIV);
          query.bindValue(":DATELIV", DATELIV);
          query.bindValue(":STATUTLIV", STATUTLIV);



return  query.exec();
}
bool Livraisons::numExists(const int &NUMLIV)
{
    QSqlQuery query;
    QString res = QString::number(NUMLIV);
    query.prepare("SELECT NUMLIV FROM LIVRAISONS WHERE NUMLIV=:NUMLIV");
    query.bindValue(":NUMLIV", res);

    if (query.exec() && query.next()) //execute the sql query w next to move on to the next row//
    {
        // If a row is fetched, the number exists in the database.
        return true;
    }

    // If no rows were fetched, the number does not exist.
    return false;
}

