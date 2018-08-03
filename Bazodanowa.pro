#-------------------------------------------------
#
# Project created by QtCreator 2018-04-22T12:02:51
#
#-------------------------------------------------

QT       += core gui widgets sql xml


TARGET = Bazodanowa
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

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
    onemonthcompanydata.cpp \
    xmlcreator.cpp

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
    onemonthcompanydata.h \
    xmlcreator.h

FORMS    += mainwindow.ui \
    addcompanydialog.ui \
    contractorsdialog.ui \
    tableDialog.ui \
    invoicecreatordialog.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    k.xml

