#include "mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include <iostream>
#include "employe.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    employe e;
    qDebug();


    Connection c;
    bool test=c.createconnect();
    login l;
    MainWindow w;
    l.show();
    if(test)
    {
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}

