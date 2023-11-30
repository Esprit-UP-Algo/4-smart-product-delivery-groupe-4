#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include "arduino.h"
#include "ui_login.h"
#include "login.h"
#include "connection.h"
#include "mainwindow.h"
#include "arduino.h"
#include"widget.h"
#include "employe.h"
#include "oublier.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
 ui->setupUi(this);
        int ret = A.connect_arduino();
        switch (ret) {
        case 0:
            qDebug() << "Arduino est disponible et connecté à : " << A.getarduino_port_name();
            break;
        case 1:
            qDebug() << "Arduino est disponible mais non connecté à : " << A.getarduino_port_name();
            break;
        case -1:
            qDebug() << "Arduino n'est pas disponible";
            break;
        }

        QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));

  }
login::~login()
{
    delete ui;
}

void login:: on_pushButton_login_clicked()
{
    QString CIN = ui->lineEdit_username->text();
       QString mdp = ui->lineEdit_password->text();
      QSqlQuery query;
      query.prepare("SELECT * FROM EMPLOYE WHERE CIN=:CIN");
         query.bindValue(":CIN",CIN);

         if (query.exec() && query.next() && mdp=="1")
      {
          QMessageBox::information(this, QObject::tr("Login is open"),
                      QObject::tr("Username and passord is correct.\n"
                                  "open."), QMessageBox::Cancel);

          this->hide();
                      MaClasse *auth = new MaClasse;
                      auth->show();
      }
       else {
          QMessageBox::warning(this, QObject::tr("Login is not  open"),
                      QObject::tr("Username and passord is uncorrect.\n"
                                  "try again."), QMessageBox::Cancel);
      }


}
QSerialPort* login::getserial() {
    return A.getserial();
}



void login::update_label()
{ QByteArray data = A.getserial()->readAll();
    QString receivedData = QString::fromUtf8(data);

    if (!receivedData.isEmpty()) {
        // Supposons que les données série contiennent uniquement l'UID
        QString badgeCode = receivedData.trimmed();
        qDebug() << badgeCode;



        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYE WHERE RFID=:badgeCode ");
        query.bindValue(":badgeCode", badgeCode);
        QString badgeCode1 = receivedData;
               badgeCode1.remove(QChar(' '));

        if (query.exec() && query.next()) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Login réussi avec succès.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            this->hide();
                        MaClasse *auth = new MaClasse;
                        auth->show();

                         // Mettre à jour l'écran LCD avec l'identifiant

        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                QObject::tr("Veuillez vérifier le badge.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    }


      }
