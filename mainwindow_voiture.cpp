#include "mainwindow_voiture.h"
#include "ui_mainwindow.h"
#include "voiture.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_voiture->setModel(V.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    QString matricule=ui->le_matricule->text();
    QString marque=ui->le_marque->text();
    QString modele=ui->le_modele->text();
    int puissance=ui->le_puissance->text().toInt();
  Voiture V(matricule,marque,modele,puissance);
  bool test=V.ajouter();
  QMessageBox msgBox;
  if(test)
  {
      msgBox.setText("Ajout avec succes.");
      ui->tab_voiture->setModel(V.afficher());

  }
  else
      msgBox.setText("Echec d'ajout");
      msgBox.exec();


}

void MainWindow::on_pb_supprimer_clicked()
{
    Voiture V1; V1.setmatricule(ui->le_matricule_supp->text());
    bool test=V1.supprimer(V1.getmatricule());
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->tab_voiture->setModel(V.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();

}

void MainWindow::on_pushButton_clicked()
{
    QString cherchermat = ui->cherchermat->text(); // Assuming cherchermat is the QLineEdit for entering matricule
    Voiture V;
    Voiture result = V.rechercher(cherchermat);

    if (!result.getmatricule().isEmpty()) // Assuming you have a method to check if the result is valid
    {
        QMessageBox msgBox;
        msgBox.setText("Voiture trouvée.");
        // You can display the details of the found car in the QMessageBox or use it as needed.
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Aucune voiture trouvée avec cette matricule.");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Voiture V;
       V.exportToPDF();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM produit ORDER BY id");
    ui->tab_voiture->setModel(model);

    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Update effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
}
