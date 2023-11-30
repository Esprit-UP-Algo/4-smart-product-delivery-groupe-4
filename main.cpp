#include "widget.h"
#include "aziz/arduino.h"
#include <QApplication>
#include"aziz/login.h"
#include"aziz/connection.h"
#include"aziz/mainwindow.h"
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    employe e;
    qDebug();


    Connection c;
    bool test=c.createconnect();
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
