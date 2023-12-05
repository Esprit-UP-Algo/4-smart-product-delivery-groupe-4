#ifndef PHARMACIE_H
#define PHARMACIE_H


#include<QString>
#include<QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>

class pharmacie
{
public:
    pharmacie();
    pharmacie(int,QString,QString,QString,QString);

    int getId() ;
   void setId(int);

   QString getNom();
   void setNom(QString);

   QString getHor() ;
   void setHor(QString);

   QString getAdresse();
   void setAdresse(QString);

   QString getNum();
   void setNum(QString);

   //la declaration des fonctions

   QSqlQueryModel* afficher();
   bool ajouter();
   bool supprimer(int);
   bool modifier(int  ,QString ,QString ,QString, QString) ;


   QSqlQueryModel * trie_ID();
   QSqlQueryModel * trie_NOM();


        private :
        int id;
        QString nom ;
        QString hor ;
        QString adresse ;
        QString num ;

};

#endif // PHARMACIE_H
