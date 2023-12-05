#include "widget.h"
#include "ui_widget.h"
#include "aziz/mainwindow.h"
#include "cherif/medicament_ui.h"
#include "hedy/gslivmainwindow.h"
#include "ghalia/mainwindow_commande.h"
#include "yosr/yosr/mainwindow_phar.h"


MaClasse::MaClasse(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MaClasse)
{
    ui->setupUi(this);
}

MaClasse::~MaClasse()
{
    delete ui;
}

void MaClasse::on_pushButtonemp_clicked()
{
    employe = new MainWindow(this);
    employe->show();
}
void MaClasse::on_pushButtonmedic_clicked()
{
    medicamentUI = new Medicament_ui(this);
    medicamentUI->show();
}

void MaClasse::on_pushButtonliv_clicked()
{
    w = new GSLIVmainwindow(this);
    w->show();
}

void MaClasse::on_pushButton_comm_clicked()
{
    a= new MainWindow_commande(this);
    a->show();
}

void MaClasse::on_pushButtonemp_2_clicked()
{
    c= new MainWindow_phar(this);
    c->show();
}
