QT       += core gui
QT       += core gui printsupport
QT       += core gui sql
QT += charts
QT += widgets
QT += core gui network
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aziz/arduino.cpp \
    ghalia/commande.cpp \
    ghalia/connexion.cpp \
    ghalia/mainwindow_commande.cpp \
    hedy/gslivmainwindow.cpp \
    hedy/livraisons.cpp \
    hedy/smtp.cpp \
    main.cpp \
    aziz/employe.cpp\
    aziz/login.cpp\
    aziz/mainwindow.cpp\
    aziz/oublier.cpp\
    cherif/medicament_ui.cpp\
    cherif/Medicament.cpp\
    widget.cpp \
    yosr/yosr/mainwindow_phar.cpp \
    yosr/yosr/pharmacie.cpp \
    yosr/yosr/qrcode.cpp \
    yosr/yosr/qrcodegeneratordemo.cpp \
    yosr/yosr/qrcodegeneratorworker.cpp \
    yosr/yosr/qrwidget.cpp

HEADERS += \
    aziz/arduino.h \
    aziz/employe.h\
    aziz/login.h\
    aziz/mainwindow.h\
    aziz/oublier.h\
    cherif/medicament_ui.h\
    cherif/Medicament.h\
    ghalia/commande.h \
    ghalia/connexion.h \
    ghalia/mainwindow_commande.h \
    hedy/gslivmainwindow.h \
    hedy/livraisons.h \
    hedy/smtp.h \
    widget.h \
    yosr/yosr/mainwindow_phar.h \
    yosr/yosr/pharmacie.h \
    yosr/yosr/qrcode.h \
    yosr/yosr/qrwidget.h

FORMS += \
    aziz/mainwindow.ui\
    aziz/login.ui\
    aziz/oublier.ui\
    cherif/medicament_ui.ui\
    ghalia/mainwindow_commande.ui \
    hedy/gslivmainwindow.ui \
    widget.ui \
    yosr/yosr/mainwindow_phar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
SUBDIRS += \
    aziz/PROJETQT1.pro\
    cherif/mohhamedddddd.pro\
DISTFILES += \
    aziz/PROJETQT1.pro.user\
    cherif/mohhamedddddd.pro,user\ \
    ghalia/inte.pro \
    yosr/yosr/integ.pro

RESOURCES += \
    cherif/res.qrc\
    aziz/image.qrc\
    ghaluaa.qrc \


DISTFILES += \
    ghalia/.gitignore \
    hedy/.gitignore
