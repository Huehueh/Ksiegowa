#-------------------------------------------------
#
# Project created by QtCreator 2018-04-22T12:02:51
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bazodanowa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp \
    addcompanydialog.cpp \
    contractorsdialog.cpp \
    dictionarydialog.cpp \
    saledelegate.cpp \
    purchasedelegate.cpp \
    saledialog.cpp \
    operationdialog.cpp \
    purchasedialog.cpp \
    invoicecreatordialog.cpp \
    dialogmanager.cpp \
    modeltoxmlconverter.cpp

HEADERS  += mainwindow.h \
    dbmanager.h \
    addcompanydialog.h \
    enums.h \
    columnnames.h \
    names.h \
    contractorsdialog.h \
    dictionarydialog.h \
    saledelegate.h \
    purchasedelegate.h \
    saledialog.h \
    operationdialog.h \
    purchasedialog.h \
    invoicecreatordialog.h \
    dialogmanager.h \
    jpk_names.h \
    modeltoxmlconverter.h

FORMS    += mainwindow.ui \
    addcompanydialog.ui \
    contractorsdialog.ui \
    tableDialog.ui \
    invoicecreatordialog.ui
