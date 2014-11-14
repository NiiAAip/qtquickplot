TEMPLATE = lib
TARGET = quickplotqmlplugin

QT += qml quick
CONFIG += qt plugin c++11

SOURCES += \
    vumeter.cpp \
    qpscaleengine.cpp \
    qpplotitem.cpp \
    qptightscaleengine.cpp \
    quickplotqmlplugin.cpp

HEADERS += \
    vumeter.h \
    qpscaleengine.h \
    qpplotitem.h \
    qptightscaleengine.h \
    quickplotqmlplugin.h

OTHER_FILES += \
    main.qml \
    imports/QuickPlot/Axes.qml \
    imports/QuickPlot/AxisLabels.qml \
    imports/QuickPlot/PlotArea.qml \
    imports/QuickPlot/Tick.qml \
    imports/QuickPlot/qmldir

DESTDIR = imports/QuickPlot
