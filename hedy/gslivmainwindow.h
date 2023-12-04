#ifndef GSLIVMAINWINDOW_H
#define GSLIVMAINWINDOW_H
#include "livraisons.h"
#include <QSortFilterProxyModel>
#include <QHeaderView>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GSLIVmainwindow; }
QT_END_NAMESPACE

class GSLIVmainwindow : public QMainWindow
{
    Q_OBJECT

public:
    GSLIVmainwindow(QWidget *parent = nullptr);
    ~GSLIVmainwindow();

private slots:
    void on_pb_ajouter_21_clicked();

    void on_pb_modifier_21_clicked();

    void on_pb_supprimer_21_clicked();

    void on_pb_rechercher_21_clicked();

    void on_pb_trier_21_clicked();

    void on_pb_pdf_21_clicked();

    void on_pb_stat_21_clicked();
    void sendMail();
    void mailSent(QString);
    void browse();


    void on_pushButton_back_clicked();

private:
    Ui::GSLIVmainwindow *ui;
    QStringList files;
    Livraisons L;
    QSortFilterProxyModel *proxyModel;
};
#endif // GSLIVMAINWINDOW_H
