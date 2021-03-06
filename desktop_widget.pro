#-------------------------------------------------
#
# Project created by QtCreator 2022-04-30T17:47:58
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop_widget
DESTDIR = bin/
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
SOURCES += \
    dpushbutton.cpp \
    dragbtn.cpp \
    geturldiag.cpp \
        main.cpp \
    resizebtn.cpp \
    sidebar.cpp \
    body.cpp \
    root.cpp

HEADERS += \
    dpushbutton.h \
    dragbtn.h \
    geturldiag.h \
    resizebtn.h \
    sidebar.h \
    body.h \
    root.h

FORMS += \
    dpushbutton.ui \
    geturldiag.ui \
    resizebtn.ui \
    sidebar.ui \
    body.ui \
    root.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

OBJECTS_DIR = build/obj/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/