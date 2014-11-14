TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    vumeter.cpp \
    qpscaleengine.cpp \
    qpplotitem.cpp \
    qptightscaleengine.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    vumeter.h \
    qpscaleengine.h \
    qpplotitem.h \
    qptightscaleengine.h
