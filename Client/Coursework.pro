QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth_window.cpp \
    main.cpp \
    mainwindow.cpp \
    newcontragents.cpp \
    newdocument.cpp \
    newnote.cpp \
    newobject.cpp \
    newsubjetc.cpp \
    newtreaty.cpp

HEADERS += \
    auth_window.h \
    mainwindow.h \
    newcontragents.h \
    newdocument.h \
    newnote.h \
    newobject.h \
    newsubjetc.h \
    newtreaty.h

FORMS += \
    auth_window.ui \
    mainwindow.ui \
    newcontragents.ui \
    newdocument.ui \
    newnote.ui \
    newobject.ui \
    newsubjetc.ui \
    newtreaty.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
