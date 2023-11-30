#include "widget.h"
#include "ui_widget.h"
#include "aziz/mainwindow.h"
#include "cherif/medicament_ui.h"


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
