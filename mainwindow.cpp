#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QTableWidgetItem>
#include <QStandardItem>
#include <QtCharts/QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QSqlTableModel>
#include <QDir>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QDate>
#include <QSqlError>
#include <QtCharts/QChart>
#include <QPieSeries>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFile>
#include <QSortFilterProxyModel>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>

#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextStream>
#include<QWidget>
#include <QtSvg/QSvgRenderer>
#include<QDirModel>
#include "qrcode.h"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(c.afficher());
    connect(ui->search, SIGNAL(returnPressed()), this, SLOT(on_search_returnPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajout_clicked()
{
    int id = ui->id_pha->text().toInt();

    // Vérifier que tous les champs sont remplis
        if (ui->id_pha->text().isEmpty() || ui->nom_pha->text().isEmpty() ||
            ui->hor_pha->text().isEmpty() || ui->ad_pha->text().isEmpty() ||
            ui->num_pha->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
            return;
        }


        QString nom = ui->nom_pha->text();
        QString hor = ui->hor_pha->text();
        QString adresse = ui->ad_pha->text();
        QString num = ui->num_pha->text();

        // Vérifier si l'identifiant existe déjà dans la base de données
        QSqlQuery verif_query;
        verif_query.prepare("SELECT COUNT(*) FROM PHARMACIE WHERE id = :id");
        verif_query.bindValue(":id", id);
        verif_query.exec();
        verif_query.next();
        int id_count = verif_query.value(0).toInt();

        if (id_count > 0) {
            QMessageBox::warning(this, "Erreur", "L'identifiant est déjà utilisé !");
            return;
        }

        pharmacie c(id, nom, hor, adresse, num);

        bool test = c.ajouter();
        if(test) {
            QMessageBox::information(this, "Succès", "Ajout réussi !");
            ui->tableView->setModel(c.afficher());
            ui->tableView->resizeColumnsToContents();
            stat();
        }
        else {
            QMessageBox::critical(this, "Erreur", "Ajout non effectué !");
        }
}

void MainWindow::on_supprimer_clicked()
{
    // Récupère la ligne sélectionnée dans le tableau
        int row = ui->tableView->currentIndex().row();

        // Vérifie si une ligne est sélectionnée
        if (row < 0) {
            QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner une ligne à supprimer.");
            return;
        }

        int id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();


        QMessageBox msgbox;
        msgbox.setText("Voulez-vous vraiment supprimer ces informations ?");
        msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgbox.setDefaultButton(QMessageBox::No);
        int res = msgbox.exec();


        if (res == QMessageBox::Yes) {
            pharmacie c1;
            c1.setId(id);
            bool test = c1.supprimer(c1.getId());


            if(test) {
                QMessageBox::information(this, "Succès", "Suppression avec succès");
                ui->tableView->setModel(c.afficher());

            } else {
                QMessageBox::warning(this, "Échec", "Échec de suppression");
            }
        }
}

void MainWindow::on_modifier_clicked()
{
    int id=ui->id_pha->text().toInt();


        if (ui->nom_pha->text().isEmpty() || ui->hor_pha->text().isEmpty() ||
            ui->ad_pha->text().isEmpty() || ui->num_pha->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
            return;
        }

    QString nom=ui->nom_pha->text();
    QString hor=ui->hor_pha->text();
    QString adresse=ui->ad_pha->text();
    QString num=ui->num_pha->text();


    pharmacie c(id,nom,hor,adresse,num);

     bool test=c.modifier(id,nom,hor,adresse,num);
     if(test)
     {ui->tableView->setModel(c.afficher());

         stat();
         QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modif successful.\n"
                                             "click OK to continue."),QMessageBox::Ok);

     }
     else QMessageBox::critical(nullptr, QObject::tr(" not OK"),
                                   QObject::tr("modif non effectue.\n"
                                               "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_PDF_clicked()
{
    QString dir = "C:/Users/msi/Bureau";
       QDir().mkpath(dir);
       QString fileName = dir + "/Pharmacies.pdf";
       QPdfWriter pdf(fileName);
       QPainter painter(&pdf);
       int i = 4000;
    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/msi/Downloads/logo_p.png"));//C:\Users\msi\Downloads
        painter.setPen(Qt::red);
        painter.setFont(QFont("Time New Roman", 25));
        painter.drawText(3000,1450,"Liste des Pharmacies");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(100,100,9400,2500);
        painter.drawRect(100,3000,9400,500);
        painter.setFont(QFont("Time New Roman", 10));
        painter.drawText(300,3300,"ID ");
        painter.drawText(1500,3300,"nom");
        painter.drawText(3000,3300,"Horraires");
        painter.drawText(4800,3300,"adresse");
        painter.drawText(6600,3300,"Numero");
        painter.drawRect(100,3000,9400,10700);

        QTextDocument previewDoc;
        QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

        QTextCursor cursor(&previewDoc);

        QSqlQuery query;
        query.prepare("SELECT ID, NOM, HOR, ADRESSE, NUM FROM PHARMACIE");
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
            //painter.drawText(13500,i,query.value(8).toString());

            i = i +500;
        }

        int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
            QMessageBox::Yes|QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pharmacies.pdf"));
            painter.end();
        }
        else
        {
             painter.end();
        }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &choix)
{
    pharmacie c;
        if (choix == "Nom")
        {
            bool test = c.trie_NOM();
            if (test)
            {
                ui->tableView->setModel(c.afficher());
                ui->tableView->setModel(c.trie_NOM());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri Nom effectué \n"
                                                     "Click Cancel to exist ."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("non"),
                                      QObject::tr("tri Nom failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
        else if (choix == "ID")
        {
            bool test = c.trie_ID();
            if (test)
            {
                ui->tableView->setModel(c.afficher());
                ui->tableView->setModel(c.trie_ID());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri id effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("non"),
                                      QObject::tr("tri id failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}

void MainWindow::on_search_returnPressed()
{
    QString search_text = ui->search->text().trimmed();
        QString uppercase_search_text = search_text.toUpper();

        QSqlQueryModel* model = new QSqlQueryModel();
        QString query("SELECT * FROM PHARMACIE WHERE UPPER(ID) LIKE '%' || :search_text || '%' "
                        " OR UPPER(NOM) LIKE '%' || :search_text || '%' "
                        " OR UPPER(HOR) LIKE '%' || :search_text || '%' "
                        " OR UPPER(ADRESSE) LIKE '%' || :search_text || '%' "
                        " OR UPPER(NUM) LIKE '%' || :search_text || '%' "
                      " OR UPPER(ID) LIKE '%' || :uppercase_search_text || '%' "
                      " OR UPPER(NOM) LIKE '%' || :uppercase_search_text || '%' "
                      " OR UPPER(HOR) LIKE '%' || :uppercase_search_text || '%' "
                      " OR UPPER(ADRESSE) LIKE '%' || :uppercase_search_text || '%' "
                      " OR UPPER(NUM) LIKE '%' || :uppercase_search_text || '%' ");

        QSqlQuery sql_query;
        sql_query.prepare(query);
        sql_query.bindValue(":search_text", search_text);
        sql_query.bindValue(":uppercase_search_text", uppercase_search_text);

        if (sql_query.exec())
        {
            model->setQuery(sql_query);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Horaires"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));
            ui->tableView->setModel(model);
        }
        else
        {
            qDebug() << "Error executing query: " << sql_query.lastError().text();
        }
}

void MainWindow::on_stat_butt_clicked()
{

          QChart *chart = new QChart();

          // Set the chart title
          chart->setTitle("Secteurs");

          // Create a pie series and add it to the chart
          QPieSeries *series = new QPieSeries();

          // Query the database to get the data for the chart
          QSqlQuery query;
          query.prepare("SELECT ADRESSE, COUNT(*) FROM PHARMACIE GROUP BY ADRESSE");
          if(query.exec())
          {
              int total = 0;
              while(query.next())
              {
                  // Get the type and count for the current row
                  QString type = query.value(0).toString();
                  int count = query.value(1).toInt();

                  // Add the type and count to the series
                  series->append(type, count);

                  // Increment the total count
                  total += count;
              }

              // Set the series as the data source for the chart
              chart->addSeries(series);

              // Set the chart legend to show the percentage values
              QPieSlice *slice;
              foreach(slice, series->slices()) {
                  slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
              }

              // Create a chart view and set its size
              QChartView *chartView = new QChartView(chart, this);
              chartView->setRenderHint(QPainter::Antialiasing);
              chartView->resize(800, 600);

              // Create a layout for the chart view widget and add it to the frame
              QVBoxLayout *layout = new QVBoxLayout(ui->frame_stat);
              layout->addWidget(chartView);
              ui->frame_stat->setLayout(layout);
          }
}


void MainWindow::on_QR_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir un identifiant.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int le_id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(le_id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    svgRenderer.render( &pixPainter );
                    ui->QRCODE_3->setPixmap(pix);

               }
}
