#include "voiture.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QColor>
#include <QFont>
#include <QString>
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QUrlQuery>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "voiture.h"
#include <QSqlQuery>
#include <QPainter>
#include <QtDebug>
#include <QObject>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>

Voiture::Voiture()
{
    matricule=" "; marque=" "; modele=" " ;puissance=0;

}
Voiture::Voiture(QString matricule,QString marque,QString modele,int puissance)
{
this->matricule=matricule;
this->marque=marque;
this->modele=modele;
this->puissance=puissance;
 }
QString Voiture::getmatricule(){return matricule;}
QString Voiture::getmarque(){return marque;}
QString Voiture::getmodele(){return modele;}
int Voiture::getpuissance(){return puissance;}
void Voiture::setmatricule(QString matricule){this->matricule=matricule;}
void Voiture::setmarque(QString marque){this->marque=marque;}
void Voiture::setmodele(QString modele){this->modele=modele;}
void Voiture::setpuissance(int puissance){this->puissance=puissance;}
bool Voiture::ajouter()
{
    QSqlQuery query;
    QString puissance_string= QString::number(puissance);
          query.prepare("INSERT INTO Voiture (matricule,marque,modele,puissance) "
                        "VALUES (:matricule, :marque, :modele, :puissance)");
          query.bindValue(":matricule", matricule);
          query.bindValue(":marque", marque);
          query.bindValue(":modele", modele);
          query.bindValue(":puissance", puissance_string);
          return  query.exec();
}
bool Voiture::supprimer(QString matricule)
{
    QSqlQuery query;
          query.prepare(" delete from Voiture where matricule=:matricule");
          query.bindValue(":matricule", matricule);

          return  query.exec();
}
QSqlQueryModel* Voiture::afficher(){
 QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT* FROM Voiture");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("marque"));
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("model"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("puissance"));

 return model ;

}

Voiture Voiture::rechercher(QString matricule)
{
    Voiture result;

    // Implement the logic to search for a car based on matricule
    // You may use QSqlQuery or any other method based on your data storage mechanism

    // Example using QSqlQuery:
    QSqlQuery query;
    query.prepare("SELECT * FROM Voiture WHERE matricule = :matricule");
    query.bindValue(":matricule", matricule);

    if (query.exec() && query.next())
    {
        result.setmatricule(query.value(0).toString());
        result.setmarque(query.value(1).toString());
        result.setmodele(query.value(2).toString());
        result.setpuissance(query.value(3).toInt());
    }

    return result;
}

void Voiture::exportToPDF() {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QString fileName = QFileDialog::getSaveFileName(nullptr, "Export PDF", "", "PDF Files (*.pdf)");
        if (fileName.isEmpty()) {
            return;
        }
        printer.setOutputFileName(fileName);

        QPainter painter;
        painter.begin(&printer);

        QFont font("Arial", 12);
        painter.setFont(font);

        // Title
        painter.drawText(100, 100, "LA LISTE DES PRODUITS");

        QSqlQueryModel* model = afficher();

        // Set up the table headers
        int x = 100;
        int y = 150;
        int cellWidth = 80;
        int cellHeight = 30;

        // Background gradient for the entire table
        QLinearGradient backgroundGradient(x, y, x, y + model->rowCount() * cellHeight);
        backgroundGradient.setColorAt(0, QColor(200, 200, 255));  // Light blue
        backgroundGradient.setColorAt(1, QColor(255, 255, 255));  // White
        painter.fillRect(x, y, model->columnCount() * cellWidth, model->rowCount() * cellHeight, backgroundGradient);

        painter.drawLine(x, y, x + model->columnCount() * cellWidth, y);  // Horizontal line under headers

        for (int col = 0; col < model->columnCount(); ++col) {
            painter.fillRect(x, y, cellWidth, cellHeight, backgroundGradient);  // Apply the same gradient to headers
            painter.drawText(x, y, cellWidth, cellHeight, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
            painter.drawLine(x + cellWidth, y, x + cellWidth, y + cellHeight);  // Vertical line between columns
            x += cellWidth;
        }

        y += cellHeight;

        // Set up the table content
        for (int row = 0; row < model->rowCount(); ++row) {
            x = 100;
            for (int col = 0; col < model->columnCount(); ++col) {
                painter.fillRect(x, y, cellWidth, cellHeight, backgroundGradient);  // Apply the same gradient to content
                painter.drawText(x, y, cellWidth, cellHeight, Qt::AlignCenter, model->data(model->index(row, col)).toString());
                painter.drawLine(x + cellWidth, y, x + cellWidth, y + cellHeight);  // Vertical line between columns
                x += cellWidth;
            }
            y += cellHeight;
            painter.drawLine(100, y, 100 + model->columnCount() * cellWidth, y);  // Horizontal line between rows
        }

        painter.end();
    }
