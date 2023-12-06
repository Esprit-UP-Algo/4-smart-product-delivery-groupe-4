#ifndef VOITURE_H
#define VOITURE_H
#include <QString>
#include <QSqlQueryModel>
class Voiture
{

public:
    Voiture();
    Voiture(QString,QString,QString,int);
    QString getmatricule();
    QString getmarque();
    QString getmodele();
    int getpuissance();
    void setmatricule(QString);
    void setmarque(QString);
    void setmodele(QString);
    void setpuissance(int);
    bool ajouter();
    QSqlQueryModel*   afficher();
    bool supprimer(QString);
    Voiture rechercher(QString matricule);
    void exportToPDF();

private:
    QString matricule,marque,modele;
    int puissance;
};

#endif // VOITURE_H
