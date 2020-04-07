cache();

#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T05:20:59
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlarmClock
TEMPLATE = app

SOURCES += main.cpp\
    screenclock.cpp \
    screensetalarm.cpp \
    screenabout.cpp \
    screensetvolume.cpp \
    clock.cpp \
    controller.cpp \
    window.cpp \
    globalmemory.cpp

HEADERS  += \
    screenclock.h \
    screensetalarm.h \
    screenabout.h \
    screensetvolume.h \
    clock.h \
    controller.h \
    window.h \
    globalmemory.h

FORMS    += \
    screenclock.ui \
    screensetalarm.ui \
    screenabout.ui \
    screensetvolume.ui \
    window.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    Alarm.rc

win32:RC_FILE += Alarm.rc
