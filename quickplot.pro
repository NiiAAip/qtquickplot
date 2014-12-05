TEMPLATE = lib
TARGET = quickplotqmlplugin

QT += qml quick
CONFIG += qt plugin c++11

SOURCES += \
    qpscaleengine.cpp \
    qpplotitem.cpp \
    qptightscaleengine.cpp \
    quickplotqmlplugin.cpp \
    qpcurve.cpp \
    qpscrollingcurve.cpp

HEADERS += \
    qpscaleengine.h \
    qpplotitem.h \
    qptightscaleengine.h \
    quickplotqmlplugin.h \
    qpcurve.h \
    qpscrollingcurve.h

OTHER_FILES += \
    main.qml \
    imports/QuickPlot/Axes.qml \
    imports/QuickPlot/AxisLabels.qml \
    imports/QuickPlot/PlotArea.qml \
    imports/QuickPlot/Tick.qml \
    imports/QuickPlot/qmldir

target.path = $$[QT_INSTALL_QML]/QuickPlot
qmldir.path = $$[QT_INSTALL_QML]
qmldir.files = imports/QuickPlot

INSTALLS += target qmldir
