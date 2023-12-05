#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class commande
{public:
    commande();
    commande (int id,QDate datec,int total, int qte);
    QDate get_datec();
    int get_id();
    int get_total();
    int get_qte();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QString getExpectedVerificationCode(int id);
    bool supprimerAvecVerification(int id, const QString& verificationCode);
    bool modifier(int id, QDate datec);
    QSqlQueryModel * chercher_commande (int id);
    QSqlQueryModel * tri();
    QSqlQueryModel * afficher_c(const QDate &selectedDate);
    QSqlQueryModel* historique() const;
    void exporterHistoriqueTexte(const QString &nomFichier)const;



private:
    int id;
    QDate datec;
    int total;
    int qte;
};
#endif // COMMANDE_H
