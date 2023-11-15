#include "medicament_ui.h"
#include "ui_medicament_ui.h"
#include "Medicament.h"
#include "mainwindow.h"

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QIntValidator>
#include<QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSystemTrayIcon>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


Medicament_ui::Medicament_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Medicament_ui)
{
    ui->setupUi(this);
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
    mSystemTrayIcon->setVisible(true);
    verifierTableVide();
    ui->iDLineEdit->setValidator(new QIntValidator(0, 999999, this)); // only input int
    ui->prNomLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input int
    ui->nomLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input alphabetic characters
    ui->ancienneteLineEdit->setValidator(new QIntValidator(0, 999999, this)); // only input alphabetic characters
    ui->tableView->setModel(Medicament::afficher());

}


Medicament_ui::~Medicament_ui()
{
    delete ui;
}
void Medicament_ui::on_pushButton_back_clicked()
{
    MainWindow *MainWindowDialog = new MainWindow();
    MainWindowDialog->show();

    close();
}
void Medicament_ui::on_pushButton_ajout_clicked()
{
    // Get input values
    int code = ui->iDLineEdit->text().toInt();
    QString nom = ui->prNomLineEdit->text();
    QString type = ui->nomLineEdit->text();
    QString prix = ui->adresseLineEdit->text();
    QDate dateperemption = ui->dateDeNaissanceDateEdit->date();
    int qte = ui->ancienneteLineEdit->text().toInt();

    // Input validation
    if (code <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. code invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (type.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }
    if (!dateperemption.isValid()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. Date invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (prix.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Medicament  "),
                    QObject::tr("Medicament non ajouté. prix invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (qte <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. qte invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }




    Medicament existing = Medicament::findBycode(code);
    if(existing.getcode() != 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. code déjà existant.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    Medicament e(code, nom, type, dateperemption, prix, qte);

    if(e.ajouter())
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament ajouté.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->tableView->setModel(Medicament::afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}


void Medicament_ui::on_pushButton_supprimer_clicked()
{
    int code = ui->lineEdit_3->text().toInt();

    Medicament e = Medicament::findBycode(code);

    if (e.getcode() != 0) {
        if (Medicament::supprimer(code)) {
            QMessageBox::information(nullptr, QObject::tr("Supprime"),
                        QObject::tr("Supprimé.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
            ui->lineEdit_3->setText("");
            ui->tableView->setModel(Medicament::afficher());
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Supprime"),
                        QObject::tr("Medicament pas supprimé.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
        }
    } else {

        QMessageBox::warning(nullptr, QObject::tr("Supprime"),
                    QObject::tr("Le Medicament avec ce code n'existe pas.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}

void Medicament_ui::on_pushButton_refresh_clicked()
{
    ui->tableView->setModel(Medicament::afficher());
}

void Medicament_ui::on_tableView_activated(const QModelIndex &index)
{

    // Get the selected row data
    QAbstractItemModel *model = ui->tableView->model();
    int code = model->data(model->index(index.row(), 0)).toInt();
    QString nom = model->data(model->index(index.row(), 1)).toString();
    QString type = model->data(model->index(index.row(), 2)).toString();
    QDate dateperemption = model->data(model->index(index.row(), 3)).toDate();
    QString prix = model->data(model->index(index.row(), 4)).toString();
    int qte = model->data(model->index(index.row(), 6)).toInt();

    // Populate the add section fields
    ui->iDLineEdit->setText(QString::number(code));
    ui->lineEdit_pdf->setText(QString::number(code));
    ui->prNomLineEdit->setText(nom);
    ui->nomLineEdit->setText(type);
    ui->dateDeNaissanceDateEdit->setDate(dateperemption);
    ui->adresseLineEdit->setText(prix);
    ui->ancienneteLineEdit->setText(QString::number(qte));

}

void Medicament_ui::on_pushButton_modifier_clicked()
{
    int code = ui->iDLineEdit->text().toInt();
    QString nom = ui->prNomLineEdit->text();
    QString type = ui->nomLineEdit->text();
    QString prix = ui->adresseLineEdit->text();
    QDate dateperemption = ui->dateDeNaissanceDateEdit->date();
    int qte = ui->ancienneteLineEdit->text().toInt();

    if (code <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non Modifie. code invalid.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non Modifie. nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }
    if (type.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non Modifie. type invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (!dateperemption.isValid()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout Medicament"),
                    QObject::tr("Medicament non ajouté. Date invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }
    if (prix.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non Modifie. prix invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (qte <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non Modifie. Aqte invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }





    Medicament existing = Medicament::findBycode(code);
    if(existing.getcode() == 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non modifier car il n'existe pas."), QMessageBox::Cancel);
        return;
    }

    Medicament e(code, nom, type, dateperemption , prix, qte);

    if(e.modifier()) {
        QMessageBox::information(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->tableView->setModel(Medicament::afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier MEDICAMENT"),
                    QObject::tr("MEDICAMENT non modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}

void Medicament_ui::on_pushButton_pdf_clicked()
{
    qDebug() << "Clicked!!" ;
    int code = ui->lineEdit_pdf->text().toInt();
    Medicament e = Medicament::findBycode(code);
    if(e.getcode() != 0) {
        Medicament::imprimer(code);

        QMessageBox::information(nullptr, QObject::tr("PDF File created"),
                    QObject::tr("PDF File created.\n"
                                "Check your debug directory."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::warning(this, "MEDICAMENT Not Found", "The specified MEDICAMENT was not found in the database.");
    }
}


void Medicament_ui::on_radioButton_clicked()
{

    if(ui->comboBox->currentText() != "Choisir")
      ui->tableView->setModel(Medicament::trie("ASC",ui->comboBox->currentText()));
    else  ui->tableView->setModel(Medicament::afficher());
}

void Medicament_ui::on_radioButton_2_clicked()
{
    if(ui->comboBox->currentText() != "Choisir")
        ui->tableView->setModel(Medicament::trie("DESC",ui->comboBox->currentText()));
    else  ui->tableView->setModel(Medicament::afficher());
}

void Medicament_ui::on_search_field_textChanged(const QString &arg1)
{
    QString searchText = arg1.trimmed(); // Remove leading/trailing whitespaces

    // Check if the search text is empty, and if so, display the full list
    if (searchText.isEmpty()) {
        ui->tableView->setModel(Medicament::afficher());
        return;
    }

    // Attempt to convert the search text to an integer (code search)
    bool isNumeric;
    int searchcode = searchText.toInt(&isNumeric);

    // Use QSqlQuery to perform a more complex search query
    QSqlQuery query;
    if (isNumeric) {
        query.prepare("SELECT * FROM MEDICAMENT WHERE code = :code OR nom LIKE :search OR type LIKE :search");
        query.bindValue(":code", searchcode);
    } else {
        query.prepare("SELECT * FROM MEDICAMENT WHERE nom LIKE :search OR type LIKE :search");
    }

    query.bindValue(":search", "%" + searchText + "%"); // Search for partial matches

    if (query.exec()) {
        QStandardItemModel *newModel = new QStandardItemModel(0, 6, this);
        newModel->setHorizontalHeaderItem(0, new QStandardItem(QString("code")));
        newModel->setHorizontalHeaderItem(1, new QStandardItem(QString("nom")));
        newModel->setHorizontalHeaderItem(2, new QStandardItem(QString("type")));
        newModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Date de peremption")));
        newModel->setHorizontalHeaderItem(4, new QStandardItem(QString("prix")));
        newModel->setHorizontalHeaderItem(5, new QStandardItem(QString("qte")));

        while (query.next()) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(query.value("code").toString()));
            rowItems.append(new QStandardItem(query.value("nom").toString()));
            rowItems.append(new QStandardItem(query.value("type").toString()));
            rowItems.append(new QStandardItem(query.value("dateperemption").toString()));
            rowItems.append(new QStandardItem(query.value("prix").toString()));
            rowItems.append(new QStandardItem(query.value("qte").toString()));
            newModel->appendRow(rowItems);
        }

        ui->tableView->setModel(newModel);
        ui->tableView->show();
    } else {
        // Handle the case where the query execution fails
        qDebug() << "Query execution failed: " << query.lastError();
    }
}

void Medicament_ui::on_pushButton_stats_clicked()
{
    // Créez un modèle de données pour le graphique circulaire
        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        // Ajoutez des tranches (slices) pour chaque groupe d'âge
        // Vous devrez obtenir les données de votre base de données ici
        // Par exemple, supposons que vous ayez une fonction "getAgeDistribution()" qui renvoie un QHash<QString, int>
        QHash<QString, int> Distribution = Medicament::getqteTypeDistribution();

        for (const QString &Group : Distribution.keys()) {
            QtCharts::QPieSlice *slice = series->append(Group, Distribution.value(Group));
            // Vous pouvez personnaliser l'apparence de chaque tranche si vous le souhaitez
        }

        // Créez un graphique circulaire et configurez-le
        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition par Niveau");

        // Créez une vue de graphique pour afficher le graphique circulaire
        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Affichez la vue du graphique dans une nouvelle fenêtre
        QMainWindow *chartWindow = new QMainWindow(this);
        chartWindow->setCentralWidget(chartView);
        chartWindow->resize(800, 600);
        chartWindow->show();
}

void Medicament_ui::verifierTableVide() {
    Medicament medicament;
            if (medicament.Vide()) {
                mSystemTrayIcon->showMessage(tr("WARNING"),
                                             tr("Pas des medicaments disponibles pour le moument."));
       }
}
