#ifndef MACLASSE_H
#define MACLASSE_H

#include <QWidget>
#include "aziz/mainwindow.h"
#include "cherif/medicament_ui.h"
#include "hedy/gslivmainwindow.h"
#include "ghalia/mainwindow_commande.h"
#include "yosr/yosr/mainwindow_phar.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MaClasse; }
QT_END_NAMESPACE

class MaClasse : public QWidget
{
    Q_OBJECT

public:
    MaClasse(QWidget *parent = nullptr);
    ~MaClasse();

private slots:
    void on_pushButtonemp_clicked();

    void on_pushButtonmedic_clicked();

    void on_pushButtonliv_clicked();

    void on_pushButton_comm_clicked();

    void on_pushButtonemp_2_clicked();

private:
    Ui::MaClasse *ui;
    MainWindow *employe;
    Medicament_ui *medicamentUI ;
    GSLIVmainwindow *w;
    MainWindow_commande *a;
    MainWindow_phar *c;


};
#endif // MACLASSE_H
