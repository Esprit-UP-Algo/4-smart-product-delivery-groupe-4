#include "gslivmainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include<QDebug>
#include "connection.h"
#include "livraisons.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    Livraisons L;
    qDebug();
    bool test=c.createconnect();
     GSLIVmainwindow w;
     if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}


