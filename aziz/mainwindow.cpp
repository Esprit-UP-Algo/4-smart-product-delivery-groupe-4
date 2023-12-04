#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include"employe.h"
#include"connection.h"
#include <iostream>
using namespace std;
#include "arduino.h"
#include <QTextCodec>

//pdf
#include <QPrinter>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>

//stat
#include <QVBoxLayout>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE


#include "login.h"
#include "ui_login.h"
#include "widget.h"







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(e.afficher());
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_cinsupp->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_abs->setValidator(new QIntValidator(0,999,this));
    ui->lineEdit_salaire->setValidator(new QIntValidator(0,99999,this));
    ui->lineEdit_nom->setMaxLength(8);
    ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z_]{1,8}$"), this));
    ui->lineEdit_prenom->setMaxLength(8);
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z_]{1,8}$"), this));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
                switch(ret){
                case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                    break;
                case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case(-1):qDebug() << "arduino is not available";
                }
                 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(connect_RFID())); // permet de lancer
                 //le slot update_label suite à la reception du signal readyRead (reception des données)
    // Créez le widget principal
        mainWidget = new QWidget(this);
        statsWidget = new QMainWindow(this);
        // Ajoutez des composants au widget principal
        // ...

        // Exemple : Ajoutez un bouton pour afficher les statistiques
        /*QPushButton *button = new QPushButton("Afficher Statistiques", mainWidget);
        connect(button, SIGNAL(clicked()), this, SLOT(afficherStatistiques()));*/
        // Positionnez et stylisez le bouton selon vos besoins

        // Créez le widget pour les statistiques (initialement masqué)
        statsWidget = new QWidget(this);
        statsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        statsWidget->hide();

        // Ajoutez des widgets (comme votre graphique de statistiques) à statsWidget
        // ...

        // Ajoutez un bouton pour revenir à la page initiale depuis les statistiques
        QPushButton *backButton = new QPushButton("Revenir à la page initiale", statsWidget);
        connect(backButton, SIGNAL(clicked()), this, SLOT(revenirPageInitiale()));
        // Positionnez et stylisez le bouton selon vos besoins









}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_ajouter_clicked()
{
    qDebug();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString mdp=ui->lineEdit_mdp->text();
    int CINPP=ui->lineEdit_cin->text().toInt();
    int abs=ui->lineEdit_abs->text().toInt();
    QDate dateE=ui->dateEdit->date();//+++++++++++
    int salaire=ui->lineEdit_salaire->text().toInt();
    QString RFID=ui->lineEdit_RFID->text();


    employe e(nom,prenom,CINPP,abs,dateE,salaire,mdp,RFID);//++++++++++++++++++++++

    bool test=e.ajouter();
    if (test){


        ui->tableView->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_clicked()
{
    employe e;
    int CIN=ui->lineEdit_cinsupp->text().toInt();
    bool test=e.supprimer(CIN);

    if (test){
        ui->tableView->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->tableView->setModel(e.afficher());
}



void MainWindow::on_pushButton_modifier_clicked()
{
    qDebug();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString mdp=ui->lineEdit_mdp->text();
    int CIN=ui->lineEdit_cin->text().toInt();
    int abs=ui->lineEdit_abs->text().toInt();
    QDate dateE=ui->dateEdit->date();//+++++++++++++++++++
    int salaire=ui->lineEdit_salaire->text().toInt();
    QString RFID=ui->lineEdit_RFID->text();


    employe e(nom,prenom,CIN,abs,dateE,salaire,mdp,RFID);//++++++++++++++++

    bool test=e.modifier(CIN);
    if (test){


        ui->tableView->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("modifier avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" modifier non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::exportToPDF() {
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");

        if (filePath.isEmpty()) {
            // L'utilisateur a annulé la sélection du fichier
            return;
        }

        // Créer un objet QPrinter
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);

        // Créer un objet QPainter qui dessinera sur le QPrinter
        QPainter painter(&printer);

        // Commencer le dessin sur la page
        painter.begin(&printer);

        // Définir la taille de la page
        printer.setPageSize(QPrinter::A4);

        // Définir la police et la taille du texte
        painter.setFont(QFont("Arial", 12));

        // Dessiner le titre
        painter.drawText(100, 100, "Liste des employés");

        // Dessiner l'en-tête du tableau
        painter.drawText(100, 120, "Nom");
        painter.drawText(200, 120, "Prénom");
        painter.drawText(300, 120, "CIN");
        painter.drawText(400, 120, "Salaire");
        // Ajouter d'autres en-têtes selon vos besoins

        // Récupérer les données depuis la base de données
        QSqlQuery query;
        query.prepare("SELECT * FROM employe");
        if (query.exec()) {
            int row = 140;
            int rowCount = 0;
            while (query.next()) {
                QString nom = query.value("nom").toString();
                QString prenom = query.value("prenom").toString();
                int cin = query.value("CIN").toInt();
                int salaire = query.value("salaire").toInt();
                // Ajouter d'autres colonnes selon vos besoins

                // Dessiner les données des employés
                painter.drawText(100, row, nom);
                painter.drawText(200, row, prenom);
                painter.drawText(300, row, QString::number(cin));
                painter.drawText(400, row, QString::number(salaire));
                // Ajouter d'autres colonnes selon vos besoins

                row += 20; // Augmenter la position Y pour la prochaine ligne
                rowCount++;

                // Passer à une nouvelle page après un certain nombre de lignes (par exemple, 20 lignes)
                if (rowCount % 20 == 0) {
                    printer.newPage();
                    row = 100; // Réinitialiser la position Y pour la nouvelle page
                }
            }
        } else {
            // Gestion de l'erreur de la requête
            QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution de la requête SQL : " + query.lastError().text());
        }

        // Terminer le dessin sur la page
        painter.end();

        // Afficher un message de succès
        QMessageBox::information(this, "Export PDF", "Les données des employés ont été exportées avec succès vers un fichier PDF.");
}

void MainWindow::on_pushButton_pdf_clicked()
{
    exportToPDF();
}







void MainWindow::afficherStatistiques() {
    QBarSeries *series = new QBarSeries();

    // Récupérer les données d'absence depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT nom, abs FROM employe");
    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value("nom").toString();
            int abs = query.value("abs").toInt();

            QBarSet *absenceSet = new QBarSet(nom);
            *absenceSet << abs;

            series->append(absenceSet);
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête SQL : " << query.lastError().text();
        // Gérez l'erreur de la requête SQL ici
        return;
    }

    // Créer le graphique et y ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);

    // Créer l'axe X et définir le titre
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        chart->addAxis(axisX, Qt::AlignBottom);
        axisX->setTitleText("employées");
        series->attachAxis(axisX);
    /*
        // Créer l'axe Y et définir le titre
        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Nombre d'absences");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    */




        // Créer l'axe Y et définir le titre
        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Nombre d'absences");

        // Configurer l'axe pour afficher des étiquettes entières
        axisY->setLabelFormat("%d");
        axisY->setTickCount(10);  // Nombre de marques sur l'axe, ajustez selon vos besoins

        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        // Créer la vue du graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

    // Créer une nouvelle fenêtre pour afficher le graphique
    QMainWindow *statsWindow = new QMainWindow();
    statsWindow->setCentralWidget(chartView);

    // Ajouter un bouton de fermeture
    QPushButton *closeButton = new QPushButton("Fermer", statsWindow);
    closeButton->setStyleSheet("background-color: green; color: white;");  // Changer la couleur du fond et du texte
    QObject::connect(closeButton, &QPushButton::clicked, statsWindow, &QMainWindow::close);


    // Créer un layout pour organiser le bouton
    QVBoxLayout *layout = new QVBoxLayout(statsWindow);
    layout->addWidget(chartView);
    layout->addWidget(closeButton);

    // Ajuster la taille de la fenêtre
    statsWindow->resize(800, 600);  // Remplacez 800 et 600 par les dimensions souhaitées

    // Afficher la nouvelle fenêtre
    statsWindow->show();
}



void MainWindow::on_pushButton_stat_clicked()
{
    afficherStatistiques();
}


void MainWindow::revenirPageInitiale() {
    // Masquer le widget pour les statistiques
    statsWidget->hide();

    // Afficher le widget principal
    mainWidget->show();
}


//*********

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    // Instanciez un objet employe
        employe e;

        // Obtenez le critère de tri sélectionné
        QString critereTri = ui->comboBox->currentText();

        // Obtenez le modèle trié en fonction du critère sélectionné
        QSqlQueryModel *modelTri;

        if (critereTri == "Salaire") {
            modelTri = e.trierParSalaire();
        } else if (critereTri == "Date d'embauche") {
            modelTri = e.trierParDateEmbauche();
        } else {
            // Gérez toute autre option ou erreur ici
            return;
        }

        // Utilisez le modèle trié pour mettre à jour votre vue (par exemple, QTableView)
        ui->tableView->setModel(modelTri);
}


/*void MainWindow::on_pushButton_rechcin_clicked()
{
    int cin = ui->lineEdit_rechcin->text().toInt(); // Supposons que vous avez un LineEdit pour entrer le CIN
        QSqlQueryModel *model = e.rechercherParCIN(cin);

        if (model)
        {
            ui->tableView_rechcin->setModel(model);
        }
        else
        {
            // Gestion de l'erreur
            qDebug()<< "Erreur lors de la recherche par CIN.";
        }

        QSqlQueryModel *result = e.rechercherParCIN(cin);

        if (result != nullptr) {
            // Check if the model is not empty
            if (result->rowCount() > 0) {
                // Display the result in the tableView_rechcin
                ui->tableView_rechcin->setModel(result);
                QMessageBox::information(nullptr, QObject::tr("Résultat de recherche"),
                    QObject::tr("Recherche réussie.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
            } else {
                QMessageBox::information(nullptr, QObject::tr("Résultat de recherche"),
                    QObject::tr("Aucun employé trouvé avec le CIN : %1").arg(cin),
                    QMessageBox::Cancel);
            }

        } else {
            // Handle the case where the search failed (invalid CIN or not found)
            QMessageBox::critical(nullptr, QObject::tr("Erreur de recherche"),
                QObject::tr("Erreur lors de la recherche par CIN."),
                QMessageBox::Cancel);
        }

}*/

/*QPixmap pixmap("C:/Users/Administrateur/Desktop/ter/arouf/image/rechh.jpg");*/

void MainWindow::on_pushButton_rechcin_clicked()
{
    employe e;

    // Récupération du CIN depuis le lineEdit
    int CIN = ui->lineEdit_rechcin->text().toInt();

    // Appel de la fonction de recherche avec le CIN récupéré et la vue de table
   e.rechercher(ui->tableView,CIN);


}

void MainWindow::on_pushButton_raf_clicked()
{
    ui->tableView->setModel(e.afficher());
}


void MainWindow::on_pushButton_deconect_clicked()
{
    this->hide();
    login *auth = new login;
    auth->show();
}
void MainWindow::connect_RFID()

{
    // pour tester si la connexion lors du passage de la carte rfid a ete effectué ou non avec un label 'RFID_Label'
    //ui->RFID_Label->setText("arduino detecte");

    data=A.read_from_arduino();
    QString uid = QTextCodec::codecForMib(106)->toUnicode(data);

    qDebug()<<uid;//pour tester dans la console de QT

    //ui->RFID_Label->setText(uid);/*------- pour tester avec un label----------*/

    employe e; //remplacez avec le nom de votre classe

     // cas ou elle n'existe
    if(e.rfidExists(uid))

        {

            QByteArray data1;
            data1.append('1');
            A.write_to_arduino(data1);//envoie 1 a arduino et enclenche /demarre le processus 1

            qDebug()<<"carte existante";

            //prend la valeur du nom
            QString nom = e.rfidName(uid);
            //ui->RFID_NOM->setText(nom);
            //ui->stackedWidget->setCurrentIndex(2); redirige ves la page 3 de votre application.a activer seulement si vous avez un systeme de stacked Widget


            QByteArray nomData(nom.toUtf8(), 8);
            A.write_to_arduino(nomData);

        }

    // cas ou elle n'existe pas
    else if (!e.rfidExists(uid))
        {
            //inexistante
                QByteArray data1;
                data1.append('2');
                A.write_to_arduino(data1); // envoie 2 a arduino et enclenche /demarre le processus 2

                qDebug()<<"carte inexistante";

        }

    }

void MainWindow::on_pushButton_back_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();
    close();

}
