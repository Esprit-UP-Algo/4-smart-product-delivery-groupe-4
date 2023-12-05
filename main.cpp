#include "widget.h"
#include "aziz/arduino.h"
#include <QApplication>
#include"aziz/login.h"
#include "ghalia/connexion.h"
#include"aziz/mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    employe e;
    qDebug();

    bool test=c.ouvrirConnexion();
    login l;
arduino A;
    MainWindow w;
    l.show();
    if(test)
    {
        /*QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}
