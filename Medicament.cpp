#include "Medicament.h"
#include "medicament_ui.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include <QDate>

Medicament::Medicament()
{
    code = 0;
    qte = 0;
}
Medicament::Medicament(int code, QString nom, QString type, QDate dateperemption , QString prix, int qte)
{
    this->code = code;
    this->nom = nom;
    this->type = type;
    this->dateperemption = dateperemption;
    this->prix = prix;
    this->qte = qte;
}
int Medicament::getcode() const {
    return code;
}

QString Medicament::getnom() const {
    return nom;
}

QString Medicament::gettype() const {
    return type;
}

QDate Medicament::getdateperemption() const {
    return dateperemption;
}

QString Medicament::getprix() const {
    return prix;
}

int Medicament::getqte() const {
    return qte;
}

// Setters
void Medicament::setcode(int code) {
    this->code= code;
}

void Medicament::setnom(const QString &nom) {
    this->nom = nom;
}

void Medicament::settype(const QString &type) {
    this->type = type;
}

void Medicament::setdateperemption(const QDate &dateperemption) {
    this->dateperemption = dateperemption;
}

void Medicament::setprix(const QString &prix) {
    this->prix = prix;
}

void Medicament::setqte(int qte) {
    this->qte = qte;
}

// CRUD
bool Medicament::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO MEDICAMENT (code,nom, type, dateperemption, prix,qte) VALUES (:code, :nom, :type, :dateperemption, :prix, :qte)");
    q.bindValue(":code", code);
    q.bindValue(":nom", nom);
    q.bindValue(":type", type);
    q.bindValue(":dateperemption", dateperemption);
    q.bindValue(":prix", prix);
    q.bindValue(":qte", qte);

    return q.exec();
}
QSqlQueryModel* Medicament::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MEDICAMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("dateperemption"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("qte"));

    return model;
}

bool Medicament::supprimer(int code)
{
    QSqlQuery q;
    q.prepare("DELETE FROM MEDICAMENT WHERE code = :code");
    q.bindValue(":code", code);

    return q.exec();
}

Medicament Medicament::findBycode(int code)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM MEDICAMENT WHERE code = :code");
    q.bindValue(":code", code);

    if (q.exec() && q.next()) {
        QString nom = q.value("nom").toString();
        QString type= q.value("type").toString();
        QDate dateperemption = q.value("dateperemption").toDate();
        QString prix = q.value("prix").toString();
        int qte = q.value("qte").toInt();
        return Medicament(code, nom, type , dateperemption, prix , qte);
    }

    return Medicament();
}

bool Medicament::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE MEDICAMENT SET nom = :nom, type = :type, dateperemption = :dateNdateperemptionaissance, prix = :prix, qte = :qte WHERE code = :code");
    q.bindValue(":nom", nom);
    q.bindValue(":type", type);
    q.bindValue(":dateperemption", dateperemption);
    q.bindValue(":prix", prix);
    q.bindValue(":qte", qte);
    q.bindValue(":code", code);

    return q.exec();
}

void Medicament::imprimer(int code)
{
    QString nom;
    int y0 = 2000;
    Medicament e = findBycode(code);

    QString pdfFileName = QString::number(e.getcode()) + "_" + e.getnom() + "_" + e.gettype() + ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setFullPage(QPrinter::A4);
    printer.setOutputFileName(pdfFileName);

    QPainter painter(&printer);
    painter.setFont(QFont("Verdana", 30));
    painter.setPen(QColor(Qt::green)); // Set color to dark blue

    painter.drawText(200, 1000, "Fiche des medicament");
    painter.setPen(QColor(Qt::blue)); // Set color to dark blue

    painter.setFont(QFont("Verdana", 12));
    y0 += 250;
    painter.drawText(400, y0, "Nom de l'Application : PharmaDeliver");
    y0 += 500;

    QFont titleFont("Verdana", 12, QFont::Bold);
    titleFont.setUnderline(true);
    titleFont.setCapitalization(QFont::AllUppercase);
    painter.setFont(titleFont);
    painter.setPen(QColor(Qt::black)); // Set color to dark blue


    QStringList subtitles = {
        "CODE",
        "NOM",
        "TYPE",
        "DATE DE PEREMPTION ",
        "PRIX",
        "QUANTITE"
    };

    QStringList contents = {
        QString::number(e.getcode()),
        e.getnom(),
        e.gettype(),
        e.getdateperemption().toString(),
        e.getprix(),
        QString::number(e.getqte())
    };

    for (int i = 0; i < subtitles.size(); ++i)
    {
        painter.drawText(400, y0, subtitles[i] + " :");
        painter.setFont(QFont("Verdana", 12)); // Set content font to normal
        painter.drawText(4000, y0, contents[i]);
        painter.setFont(titleFont); // Reset font to subtitle style
        y0 += 250;
    }

    painter.end();
}



QSqlQueryModel* Medicament::trie(QString croissance, QString critere)
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery query;

    QString sqlQuery = "SELECT * FROM MEDICAMENT ORDER BY %1 %2";
    sqlQuery = sqlQuery.arg(critere).arg(croissance);

    query.prepare(sqlQuery);
    if (query.exec()) {
        modal->setQuery(query);
    }

    return modal;
}
QHash<QString, int> Medicament::getqteTypeDistribution()
{
    QHash<QString, int> qteTypeDistribution;

    // Récupérez la liste des médicaments depuis votre base de données
    // Par exemple, vous pouvez utiliser votre fonction afficher() pour obtenir une liste de tous les médicaments.
    QSqlQueryModel* model = afficher();

    for (int row = 0; row < model->rowCount(); ++row) {
        int qte = model->data(model->index(row, 5)).toInt(); // Supposons que la quantité est dans la colonne 5
        QString type = model->data(model->index(row, 2)).toString(); // Supposons que le type est dans la colonne 7

        // Mettez à jour la répartition par type
        if (qteTypeDistribution.contains(type)) {
            qteTypeDistribution[type] += qte;
        } else {
            qteTypeDistribution[type] = qte;
        }
    }

    return qteTypeDistribution;
}
bool Medicament::Vide() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM MEDICAMENT");
    if (query.exec() && query.next()) {
        int rowCount = query.value(0).toInt();
        return rowCount == 0;
    }
    return false; // En cas d'erreur ou autre problème
}

// ... Autres inclus

QSqlQueryModel* Medicament::afficherPeremptionMoinsUnMois()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Obtenez la date actuelle
    QDate currentDate = QDate::currentDate();

    // Soustrayez un mois de la date actuelle
    QDate oneMonthAgo = currentDate.addMonths(-1);

    // Exécutez la requête pour obtenir les médicaments dont la date de péremption est inférieure à un mois
    QSqlQuery query;
    query.prepare("SELECT * FROM MEDICAMENT WHERE dateperemption <= :currentDate AND dateperemption >= :oneMonthAgo");
    query.bindValue(":currentDate", currentDate);
    query.bindValue(":oneMonthAgo", oneMonthAgo);

    if (query.exec()) {
        model->setQuery(query);
        // Définissez les en-têtes de colonnes si nécessaire
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        // ... Définissez les en-têtes pour d'autres colonnes
    }

    return model;
}
