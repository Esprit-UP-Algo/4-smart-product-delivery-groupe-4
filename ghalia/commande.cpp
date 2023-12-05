#include "commande.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QFile>
commande::commande()
{
id=0;
total=0;
qte=0;


}
commande::commande (int id,QDate datec,int total,int qte)
{
  this->id=id;
  this->datec=datec;
  this->total=total;
  this->qte=qte;
}

QDate commande::get_datec(){return  datec;}
int commande::get_id(){return  id;}
int commande::get_total(){return total;}
int commande::get_qte(){return qte;}


bool commande::ajouter()
{
QSqlQuery query;
QString ch_id= QString::number(id);
QString ch_total=QString::number(total);
QString ch_qte=QString::number(qte);

query.prepare("insert into COMMANDE (id,datec,total,qte)""values (:id, :datec, :total, :qte)");
query.bindValue(":id", ch_id);
query.bindValue(":datec", datec);
query.bindValue(":total", ch_total);
query.bindValue(":qte", ch_qte);
return    query.exec();

}

QSqlQueryModel * commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from commande");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEC"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TOTAL"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("QTE"));

    return model;
}

/*bool commande::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from commande where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}*/
QString commande::getExpectedVerificationCode(int id)
{
    // Logique pour récupérer le code de vérification attendu en fonction de l'identifiant
    // Par exemple, vous pouvez utiliser une base de données, une table de correspondance, ou une autre méthode de stockage des codes de vérification

    // Supposons que vous ayez une table de correspondance des codes de vérification
    // où vous associez chaque identifiant à un code de vérification

    QMap<int, QString> verificationCodeMap;
    verificationCodeMap[1] = "1234";
    verificationCodeMap[2] = "5678";
    verificationCodeMap[3] = "9012";

    // Vérifier si l'identifiant existe dans la table de correspondance
    if (verificationCodeMap.contains(id)) {
        return verificationCodeMap.value(id);
    } else {
        // Si l'identifiant n'a pas de code de vérification correspondant, vous pouvez retourner une valeur par défaut ou générer un code de vérification aléatoire.
        return ""; // Retourner une chaîne vide pour indiquer l'absence de code de vérification pour cet identifiant
    }
}

bool commande::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM commande WHERE ID = :id ");
    query.bindValue(":id", res);
    bool success = query.exec();

    if (success && query.numRowsAffected() > 0) {
        return true; // Suppression réussie
    } else {
        return false; // La commande n'existe pas ou la suppression a échoué
    }
}

bool commande::modifier(int id, QDate datec)
{
    QSqlQuery query;
        query.prepare("UPDATE COMMANDE SET datec = :datec WHERE id = :id");
        query.bindValue(":datec", datec);
        query.bindValue(":id", id);
        return query.exec();


}
QSqlQueryModel * commande::chercher_commande(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
          QSqlQuery query;
          query.prepare("SELECT * FROM COMMANDE WHERE ID = :id");
          query.bindValue(":id", id);
          query.exec();

          model->setQuery(query);

           return model;
}
QSqlQueryModel * commande::afficher_c(const QDate  &selectedDate)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QString queryString = QString("SELECT id, datec, total , qte FROM commande WHERE Datec = :selectedDate");
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":selectedDate", selectedDate);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("datec"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("total"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte"));
    }

    return model;
}
QSqlQueryModel* commande::tri()
{
    QSqlQueryModel * model=new QSqlQueryModel();

        model->setQuery("select * from commande ORDER BY id");

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));

        return model;
}
QSqlQueryModel* commande::historique() const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM commande ORDER BY TO_DATE(datec, 'DD/MM/YYYY') DESC");
    if (query.exec()) {
        model->setQuery(query);
    }
    return model;
}
void commande::exporterHistoriqueTexte(const QString &nomFichier) const
{
    QFile file(nomFichier);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "Liste des Commandes\n\n";

        QSqlQueryModel *model = historique();

        for (int row = 0; row < model->rowCount(); ++row)
        {
            stream << "id: " << model->data(model->index(row, 2)).toString() << "\t";
            stream << "datec: " << model->data(model->index(row, 1)).toString() << "\t";
            stream << "total: " << model->data(model->index(row, 0)).toString() << "\t";
            stream << "qte: " << model->data(model->index(row, 3)).toString() << "\n";
        }

        file.close();
    }
    else {
        qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
    }
}
