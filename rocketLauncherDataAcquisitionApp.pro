#-------------------------------------------------
#
# Project created by QtCreator 2015-12-26T12:43:53
#
#-------------------------------------------------

QT       += core gui printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rocketLauncherDataAcquisitionApp
TEMPLATE = app
CONFIG += C++11 Wall


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    timeplotwidget.cpp \
    connectiontabwidget.cpp \
    datadisplaywidget.cpp \
    statuswidget.cpp \
    dataloggingwidget.cpp \
    packetreceiver.cpp \
    packet.cpp \
    harness.cpp \
    hexdump.cpp \
    winddataanalyzer.cpp \
    guipacket.cpp \
    helperfunctions.cpp \
    serialmanager.cpp \
    datalogger.cpp \
    settingswidget.cpp \
    defaultvalues.cpp \
    batterychargecalculator.cpp \
    linearfunction.cpp \
    settingsmanager.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    timeplotwidget.h \
    connectiontabwidget.h \
    datadisplaywidget.h \
    statuswidget.h \
    dataloggingwidget.h \
    serialmanager.h \
    packetreceiver.h \
    packet.h \
    winddirection.h \
    helperfunctions.h \
    harness.h \
    hexdump.h \
    winddataanalyzer.h \
    guipacket.h \
    datalogger.h \
    settingswidget.h \
    defaultvalues.h \
    batterychargecalculator.h \
    linearfunction.h \
    settings.h \
    settingsmanager.h

win32:CONFIG(release, debug|release): LIBS += -LD:/Libraries/Software/qwt-6.1.2/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Libraries/Software/qwt-6.1.2/lib/ -lqwtd

!win32 {
    LIBS += -lqwt
}

RESOURCES += \
    img.qrc
