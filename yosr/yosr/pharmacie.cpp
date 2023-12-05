#include "../yosr/pharmacie.h"

pharmacie::pharmacie()
{
    id = 0;
    nom = " " ;
    hor = " " ;
    adresse = " " ;
    num= " " ;
}
pharmacie::pharmacie(int id, QString nom, QString hor, QString adresse, QString num)
{
    this->id=id;
    this->nom=nom;
    this->hor=hor;
    this->adresse=adresse;
    this->num=num;
}
int pharmacie::getId()
{return id; }
void pharmacie::setId(int id )
{ this->id = id ;}


QString pharmacie::getNom()
{return nom ; }
void pharmacie::setNom(QString nom)
{this->nom = nom ;}


QString  pharmacie::getHor()
{return hor ; }
void  pharmacie::setHor(QString hor)
{this->hor = hor ;}


QString  pharmacie::getAdresse()
{return adresse ; }
void  pharmacie::setAdresse(QString adresse )
{this->adresse = adresse ; }


QString pharmacie::getNum()
{return num; }
void pharmacie::setNum (QString num)
{ this->num = num ;}

QSqlQueryModel* pharmacie::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM PHARMACIE");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Horaires"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));



  return model;}


bool pharmacie::ajouter()
{
 QSqlQuery query;
 QString id_string=QString::number(id);

       query.prepare("INSERT INTO PHARMACIE (id,nom,hor,adresse,num) "
                     "VALUES (:id, :nom, :hor, :adresse, :num)");
       query.bindValue(":id", id_string);
       query.bindValue(":nom", nom);
       query.bindValue(":hor", hor);
       query.bindValue(":adresse",adresse);
       query.bindValue(":num", num);


       return query.exec();

}


bool pharmacie::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);

          query.prepare(" Delete from PHARMACIE where id=:id");
          query.bindValue(0, id_string);



    return query.exec();
}

bool pharmacie::modifier(int id ,QString nom ,QString hor ,QString adresse,QString num)
{
    QSqlQuery query;
    QString id_string=QString::number(id);

          query.prepare("update PHARMACIE set id=:id,nom=:nom,hor=:hor,adresse=:adresse,num=:num where id=:id");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":hor", hor);
          query.bindValue(":adresse",adresse);
          query.bindValue(":num", num);



  return query.exec();
}

QSqlQueryModel * pharmacie::trie_ID()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM PHARMACIE ORDER BY id ASC");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Horaires"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));

    return model;
}
QSqlQueryModel * pharmacie::trie_NOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PHARMACIE ORDER BY nom ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Horaires"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));
    return model;
}
