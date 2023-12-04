#include "gslivmainwindow.h"
#include<QApplication>
#include<iostream>
#include "smtp.h"
#include"widget.h"
#include "connection.h"
using namespace std;
#include "ui_gslivmainwindow.h"
#include "livraisons.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QtDebug>
#include <QString>

#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QStackedWidget>
#include <QtCharts>
#include <QSqlQuery>

#include<QPrinter>
#include<QPainter>
#include<QPdfWriter>
#include<QTextTable>
#include<QTextDocument>

GSLIVmainwindow::GSLIVmainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GSLIVmainwindow)
{
    ui->setupUi(this);
    ui->numliv->setValidator(new QIntValidator(0, 999999, this));
    ui->numliv_m_4->setValidator(new QIntValidator(0, 999999, this));
    ui->numero->setValidator(new QIntValidator(0, 999999, this));

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    ui->tablivraisons->setModel(L.afficher());
    proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(L.afficher());
        ui->tablivraisons->setModel(proxyModel);
        ui->dateliv->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"),this));
        ui->dateliv_m->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"),this));


}




void GSLIVmainwindow::on_pb_ajouter_21_clicked()
{
    qDebug();
     int NUMLIV=ui->numliv->text().toInt();
     QString DATELIV=ui->dateliv->text();
     QString ADRESSELIV=ui->adresseliv->text();
     QString STATUTLIV=ui->statutliv->currentText();

     Livraisons L(NUMLIV,DATELIV,ADRESSELIV,STATUTLIV);
     bool test=L.ajouter();
     if (test){



         QMessageBox::information(nullptr, QObject::tr("ok"),
                     QObject::tr("ajout avec success.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tablivraisons->setModel(L.afficher());

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
                     QObject::tr(" ajout non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void GSLIVmainwindow::on_pb_modifier_21_clicked()
{
    {
        int NUMLIV = ui->numliv_m_4->text().toInt();
        Livraisons L;
        L.setNUMLIV(NUMLIV);
        QString newDATELIV=ui->dateliv_m->text();
        QString newADRESSELIV=ui->adresseliv_m->text();
        QString newSTATUTLIV=ui->statutliv_m->currentText();

        if (!L.numExists(NUMLIV)) {
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                    QObject::tr("Le numero n'existe pas dans la base de données. Veuillez choisir un identifiant unique."), QMessageBox::Ok);
                return; // number already exists, so don't proceed with modification.
            }

        // If the num is unique and changes are made, update the livraison's information.
        L.setNUMLIV(NUMLIV);
        L.setADRESSELIV(newADRESSELIV);
        L.setSTATUTLIV( newSTATUTLIV);
        L.setDATELIV(newDATELIV);

        bool test = L.modifier();

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modification avec succès.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tablivraisons->setModel(L.afficher()); // Mise à jour
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("La Modification a échoué.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
}

void GSLIVmainwindow::on_pb_supprimer_21_clicked()
{
    int NUMLIV = ui->numero->text().toInt();

    if (NUMLIV==-1) {
        // Show an error message if the number input is empty.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Veuillez entrer un numero avant de tenter de supprimer."), QMessageBox::Ok);
        return;
    }

    // Check if the number exists in the database.
    Livraisons L;
    L.setNUMLIV(NUMLIV);

    if (L.numExists(NUMLIV)) {
        // The ID exists, so proceed with the deletion.
        bool test = L.supprimer(L.getNUMLIV());

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression avec succès.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tablivraisons->setModel(L.afficher()); // Mise à jour
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("La suppression a échoué.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else {
        // Show an error message if the ID does not exist in the database and return from the function.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("L'identifiant n'existe pas."), QMessageBox::Ok);
        return;
    }
}

void GSLIVmainwindow::on_pb_rechercher_21_clicked()
{
    int NUMLIV = ui->numero->text().toInt(); // Récupérez le numéro de livraison entré par l'utilisateur.

    // Créez un modèle de requête SQL pour afficher la livraison recherchée.
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT  * FROM livraisons WHERE NUMLIV = :NUMLIV");
    query.bindValue(":NUMLIV", NUMLIV);

    if (query.exec()) {
        model->setQuery(query);
        ui->tablivraisons->setModel(model);

    } else {
        // Gérez les erreurs de requête SQL si nécessaire.
        qDebug() << "Erreur de requête SQL : " << query.lastError().text();
    }
}

void GSLIVmainwindow::on_pb_trier_21_clicked()
{
   ui->tablivraisons->sortByColumn(0, Qt::DescendingOrder);
}

void GSLIVmainwindow::on_pb_pdf_21_clicked()
{
    QString dir = "C:/Users/Mohamed Hedy/Bureau";
       QDir().mkpath(dir);
       QString fileName = dir + "/Livraisons.pdf";
       QPdfWriter pdf(fileName);
       QPainter painter(&pdf);
       int i = 4000;
    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Mohamed Hedy/Téléchargements/logo_p.png"));//C:\Users\Mohamed Hedy\Téléchargements
        painter.setPen(Qt::red);
        painter.setFont(QFont("Time New Roman", 25));
        painter.drawText(3000,1450,"Liste des Livraisons");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(100,100,9400,2500);
        painter.drawRect(100,3000,9400,500);
        painter.setFont(QFont("Time New Roman", 10));
        painter.drawText(300,3300,"Num de liv ");
        painter.drawText(1500,3300,"Date de livraison");
        painter.drawText(3000,3300,"Adresse de livraison");
        painter.drawText(4800,3300,"Statut de livraison");
        painter.drawRect(100,3000,9400,10700);

        QTextDocument previewDoc;

        QTextCursor cursor(&previewDoc);

        QSqlQuery query;
        query.prepare("SELECT NUMLIV, DATELIV, ADRESSELIV, STATUTLIV FROM LIVRAISONS");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(1500,i,query.value(1).toString());
            painter.drawText(3000,i,query.value(2).toString());
            painter.drawText(4800,i,query.value(3).toString());
            painter.drawText(6600,i,query.value(4).toString());
            painter.drawText(8400,i,query.value(5).toString());
            //painter.drawText(10000,i,query.value(6).toString());
            //painter.drawText(11500,i,query.value(7).toString());
            //painter.drawText(13500,i,query.value((8).toString());

            i = i +500;
        }

        int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
            QMessageBox::Yes|QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Livraisons.pdf"));
            painter.end();
        }
        else
        {
             painter.end();
        }
}

void GSLIVmainwindow::on_pb_stat_21_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT STATUTLIV, COUNT(*) FROM LIVRAISONS GROUP BY STATUTLIV");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête.";
        //db.close();
        return;
    }

    // Création de la série de données pour le graphique en secteurs
    QPieSeries *series = new QPieSeries(); //est utilisé pour représenter des données en tant que diagramme en secteurs

    while (query.next()) {
        QString statutliv = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(statutliv, count);
    }

    foreach(QPieSlice *slice, series->slices()) {
        QString label = QString("%1 (%2%)")
            .arg(slice->label())
            .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }

    // Création du graphique et ajout de la série de données
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des livraisons selon le statut ");

    // Configuration du graphique
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Affichage du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    chartView->show();
}
void GSLIVmainwindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void GSLIVmainwindow::sendMail()
{
    Smtp * smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void GSLIVmainwindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
GSLIVmainwindow::~GSLIVmainwindow()
{
    delete ui;
}
void GSLIVmainwindow::on_pushButton_back_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();

    close();

}
