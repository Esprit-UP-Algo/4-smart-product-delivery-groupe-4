#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include "arduino.h"
#include "employe.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void exportToPDF();
    void afficherStatistiques();
    void revenirPageInitiale();
    QWidget *mainWidget;
    QWidget *statsWidget;

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


    QString cheminImage;

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_modifier_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_stat_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_rechcin_clicked();

    void on_pushButton_raf_clicked();

    void connect_RFID();

    void on_pushButton_deconect_clicked();

private:
    arduino A;
    Ui::MainWindow *ui;
    employe e;
    QByteArray data;
};
#endif // MAINWINDOW_H
