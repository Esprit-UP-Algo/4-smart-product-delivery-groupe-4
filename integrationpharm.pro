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
    hedy/connection.cpp \
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
    widget.cpp

HEADERS += \
    aziz/arduino.h \
    aziz/employe.h\
    aziz/login.h\
    aziz/mainwindow.h\
    aziz/oublier.h\
    cherif/medicament_ui.h\
    cherif/Medicament.h\
    hedy/connection.h \
    hedy/gslivmainwindow.h \
    hedy/livraisons.h \
    hedy/smtp.h \
    widget.h

FORMS += \
    aziz/mainwindow.ui\
    aziz/login.ui\
    aziz/oublier.ui\
    cherif/medicament_ui.ui\
    hedy/gslivmainwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
SUBDIRS += \
    aziz/PROJETQT1.pro\
    cherif/mohhamedddddd.pro\
DISTFILES += \
    aziz/PROJETQT1.pro.user\
    cherif/mohhamedddddd.pro,user\

RESOURCES += \
    cherif/res.qrc\
    aziz/image.qrc\

DISTFILES += \
    hedy/.gitignore
