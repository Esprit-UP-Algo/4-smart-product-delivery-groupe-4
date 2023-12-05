#ifndef ARDUINO_H
#define ARDUINO_H

#include <QByteArray>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSqlQuery>

class Arduino

        {
        public:
            Arduino();
            int connect_arduino();
            int close_arduino();
            QByteArray read_from_arduino();
            QSerialPort* getserial();
            QString getarduino_port_name(){return arduino_port_name;};
            QByteArray read_from_arduino2();


        private:
            QSerialPort *serial;
                static const quint16 arduino_uno_vendor_id=9025;
                static const quint16 arduino_uno_product_id=67;
                QString arduino_port_name;
                bool arduino_is_available;
                QByteArray data;
        };

#endif // ARDUINO_H
