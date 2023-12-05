#include "mainwindow_commande.h"
#include "ui_mainwindow_commande.h"
#include<QString>
#include "commande.h"
#include "widget.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <iostream>
#include <QDate>
#include <QStackedWidget>
#include <QSqlQuery>
#include <QTextStream>
#include <QFile>
#include <QChartView>
#include <QMap>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QIntValidator>
#include <QPainter>
#include <QtCharts>
#include <QTextDocument>
#include <QTextCursor>
#include <QDateTime>
#include <QIntValidator>
#include <QMainWindow>
#include <QRegularExpression>

MainWindow_commande::MainWindow_commande(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow_commande)
{
    commande c;
ui->setupUi(this);
ui->tabcommande->setModel(c.afficher());
ui->lineEdit_id->setValidator(new QIntValidator(0,99999,this));
ui->lineEdit_total->setValidator(new QIntValidator(0,99999999,this));
ui->lineEdit_qte->setValidator(new QIntValidator(0,99999,this));
//int ret=A.connect_arduino(); // lancer la connexion à arduino
//switch(ret) {
//case(0): qDebug() << "arduino is available and connected to: "<< A.getarduino_port_name(); break;
//case(1): qDebug() << "arduino is available but not connected to " <<A.getarduino_port_name(); break;
//case (-1): qDebug() << "arduino is not available";
}
//QObject::connect (A.getserial(), SIGNAL (readyRead()), this, SLOT (update_label())); // permet de lancer //le slot update_label suite à la reception du signal readyRead (reception des données).
//}

MainWindow_commande::~MainWindow_commande()
{
    delete ui;
}
void MainWindow_commande::on_pb_ajouter_clicked()
{
    // Vérification des champs remplis
    if (ui->lineEdit_id->text().isEmpty() ||
        ui->datec->date().isNull() ||
        ui->lineEdit_total->text().isEmpty() ||
        ui->lineEdit_qte->text().isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Ajouter une commande"),
                             QObject::tr("Veuillez remplir tous les champs."),
                             QMessageBox::Ok);
        return; // Arrêter l'exécution de la fonction si des champs sont vides
    }

    // Tous les champs sont remplis, on peut poursuivre l'ajout de la commande
    commande c1;
    int id_commande = ui->lineEdit_id->text().toInt();
    QDate datec_commande = ui->datec->date();
    int total_commande = ui->lineEdit_total->text().toInt();
    int qte_commande = ui->lineEdit_qte->text().toInt();
    commande c(id_commande, datec_commande, total_commande, qte_commande);
    bool test = c.ajouter();
    if (test) {
        ui->tabcommande->setModel(c1.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajouter une commande"),
                                 QObject::tr("Commande ajoutée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une commande"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->tableView->setModel(tmpcommande.afficher());
}

void MainWindow_commande::on_pb_supprimer_clicked()
{
    QString data = ui->lineEdit_id_2->text(); // Récupérer la valeur saisie dans le lineEdit
    int id = data.toInt(); // Convertir la valeur en entier

    bool test = tmpcommande.supprimer(id);
    if (test)
    {
        ui->tabcommande->setModel(tmpcommande.afficher()); // Rafraîchir le modèle du tableau
        QMessageBox::information(nullptr, QObject::tr("Supprimer une commande"),
                                 QObject::tr("Commande supprimée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une commande"),
                              QObject::tr("Erreur !\n"
                                          "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

void MainWindow_commande::update_label()
    {
    data = A.read_from_arduino();

        // Supprimer les espaces, les sauts de ligne et les retours chariot de la valeur reçue
        QRegularExpression regex("[\\s\r\n_-]");
        QRegularExpressionMatchIterator it = regex.globalMatch(data);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            data.remove(match.capturedStart(), match.capturedLength());
        }

        QString currentText = ui->lineEdit_id_2->text(); // Obtenir le texte actuel du lineEdit
        QString updatedText = currentText + data; // Ajouter la nouvelle valeur à l'ancien texte

        ui->lineEdit_id_2->setText(updatedText); // Afficher le texte mis à jour dans le lineEdit
    }

void MainWindow_commande::on_pushButton_modif_clicked()
{
    commande cm;
    int id = ui->lineEdit_id->text().toInt();
            QDate datec = ui->datec->date();

            bool test = cm.modifier(id, datec);

            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Modification effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tabcommande->setModel(cm.afficher());
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                            QObject::tr("Modification non effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(tmpcommande.afficher());
}
}

void MainWindow_commande::on_pushButton_chercher_clicked()
{
    commande c;
    int id=ui->lineEdit_id_recherche->text().toInt();
        ui->tableView_rech->setModel(c.chercher_commande(id));
}

void MainWindow_commande::on_pushButton_clicked()
{
    QSqlQuery query;
            query.exec("SELECT * FROM COMMANDE");

            QPdfWriter pdfWriter("exported_data.pdf");
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));

            pdfWriter.setPageMargins(QMarginsF(20, 20, 20, 20));

            QTextDocument pdfDoc;
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));

            pdfDoc.setDocumentMargin(20);

            QTextCursor cursor(&pdfDoc);

            while (query.next()) {
                int id = query.value("id").toInt();
                QString datec = query.value("datec").toString();
                int total = query.value("total").toInt();
                int qte = query.value("qte").toInt();


                cursor.insertText("Identifiant de la commande: "  + QString::number(id) +"\n");
                cursor.insertText("date de la commande: " + datec + "\n");
                cursor.insertText("total de la commande : " + QString::number(total) +"\n");
                cursor.insertText("quantité de la commande : " + QString::number(qte) + "\n");

                cursor.insertText("\n");
            }

            pdfDoc.print(&pdfWriter);

            QDesktopServices::openUrl(QUrl("exported_data.pdf"));
}


void MainWindow_commande::on_pushButton_stat_clicked()
    {
    QChartView *chartView = new QChartView(this);
            QChart *chart = new QChart();

            double  total,qte;

            QSqlQuery query;
            query.prepare("SELECT total,qte FROM commande ");
            if (query.exec()) {
                while (query.next())

        total = query.value("total").toDouble();
        qte = query.value("qte").toDouble();



                    QBarSeries *series = new QBarSeries();

                    QBarSet *settotal = new QBarSet("total");
                                *settotal << total;
                                series->append(settotal);

                    QBarSet *setqte = new QBarSet("qte");
                    *setqte << qte;
                    series->append(setqte);

                    chart->addSeries(series);
                }
            else {
                qDebug() << "Failed to execute query or retrieve data.";
                return;
            }


            QStringList categories;
            categories << "qte" << "total";
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            chart->createDefaultAxes();
            chart->setAxisX(axisX, chart->series().at(0));


            chartView->setChart(chart);

            QMainWindow *chartWindow = new QMainWindow(this);
            chartWindow->setCentralWidget(chartView);
            chartWindow->resize(800, 600);
            chartWindow->show();
    }
void  MainWindow_commande::on_pushButton_trier_clicked()
{
    ui->tabcommande->setModel(tmpcommande.tri());

}
void MainWindow_commande::on_calendarWidget_clicked(const QDate &datec)
{
    QSqlQueryModel *model = tmpcommande.afficher_c(datec);
    ui->tableView->setModel(model);
}

void MainWindow_commande::on_pushButton_his_clicked()
{
        commande commande;
            QString fileName = QFileDialog::getSaveFileName(this, "Exporter l'historique en texte", "", "Fichiers texte (*.txt)");
            if (!fileName.isEmpty()) {
                commande.exporterHistoriqueTexte(fileName);
                QMessageBox::information(this, "Succès", "Historique exporté sous forme de fichier texte.");
            }
    }
void MainWindow_commande::on_pushButton_2_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();

}

void MainWindow_commande::on_pushButton_12_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();
}

void MainWindow_commande::on_pushButton_11_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();
}

void MainWindow_commande::on_pushButton_10_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();
}

void MainWindow_commande::on_pushButton_9_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();
}

void MainWindow_commande::on_pushButton_8_clicked()
{
    this->hide();
    MaClasse *auth= new MaClasse;
    auth->show();
}
