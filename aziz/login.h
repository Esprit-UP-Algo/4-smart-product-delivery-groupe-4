#ifndef LOGIN_H
#define LOGIN_H
#include "employe.h"
#include <QDialog>
#include<QString>
#include <QSqlQuery>
#include <QObject>
#include <QMainWindow>
#include <QSqlError>
#include "arduino.h"
#include<QSqlQueryModel>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_login_clicked();
   // void on_lineEdit_password_textChanged(const QString &text);

QSerialPort* getserial();
    void update_label();



   // void on_pushButton_oublier_clicked();

private:
    Ui::login *ui;
    QSerialPort* serialPort;
        QByteArray data;
    arduino A;
};

#endif // LOGIN_H
