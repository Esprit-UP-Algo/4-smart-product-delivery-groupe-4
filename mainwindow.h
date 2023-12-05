#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "pharmacie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajout_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_PDF_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_search_returnPressed();

    void on_stat_butt_clicked();

    void on_pushButton_clicked();

    void on_QR_clicked();

private:
    Ui::MainWindow *ui;
    pharmacie c;
};
#endif // MAINWINDOW_H
