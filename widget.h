#ifndef MACLASSE_H
#define MACLASSE_H

#include <QWidget>
#include "aziz/mainwindow.h"
#include "cherif/medicament_ui.h"



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


private:
    Ui::MaClasse *ui;
    MainWindow *employe;
    Medicament_ui *medicamentUI ;

};
#endif // MACLASSE_H
