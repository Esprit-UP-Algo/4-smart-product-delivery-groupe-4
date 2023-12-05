#include "mainwindow_commande.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    bool test=c.ouvrirConnexion();

    MainWindow_commande w;
    if(test)
    {w.show();

        QMessageBox::information(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection avec succés.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

      return a.exec();
}
