#ifndef MAINWINDOW_COMMANDE_H
#define MAINWINDOW_COMMANDE_H
#include "commande.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow_commande; }
QT_END_NAMESPACE

class MainWindow_commande : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow_commande(QWidget *parent = nullptr);
    ~MainWindow_commande();
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_modif_clicked();

    void on_pushButton_chercher_clicked();

    void on_pushButton_clicked();

    //void on_dateEdit_userDateChanged(const QDate &date);

    //void on_datec_userDateChanged(const QDate &date);

    void on_pushButton_stat_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    //void on_pushButton_his_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_his_clicked();

    //void update_label();

    //void startVerificationProcess(int id);

    //void checkVerificationCode(const QString& codeVerification, int id);

    //void on_widget_verif_customContextMenuRequested();

private:
    Ui::MainWindow_commande *ui;
    commande tmpcommande;
    QByteArray data;
    //arduino A;
};
#endif // MAINWINDOW_COMMANDE_H


