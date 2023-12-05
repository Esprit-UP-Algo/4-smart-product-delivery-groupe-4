#ifndef LIVRAISONS_H
#define LIVRAISONS_H
#include <QString>
#include <QObject>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <iostream>
using namespace  std;




class Livraisons
{
public:
    Livraisons();
    Livraisons(int,QString,QString,QString);
    int getNUMLIV();
    QString getADRESSELIV();
    QString getSTATUTLIV();
    QString getDATELIV();
    void setNUMLIV(int);
    void setADRESSELIV(QString);
    void setSTATUTLIV(QString);
    void setDATELIV(QString);
    bool ajouter();
    QSqlQueryModel* afficher();     //QSqlQueryModel hiya tkhalik tzid data w tmanipulati qwidgets
    bool supprimer(int);
    bool modifier();
    bool numExists(const int &NUMLIV);


private:

    int NUMLIV;
    QString ADRESSELIV;
    QString STATUTLIV;
    QString DATELIV;



};

#endif // LIVRAISONS_H
