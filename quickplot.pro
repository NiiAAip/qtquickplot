TEMPLATE = lib
TARGET = quickplotqmlplugin
#CONFIG   += staticlib
QT += qml quick
CONFIG += qt plugin c++11
macx {
    #- gstreamer framework installed by the gstreamer devel installer
    BOOST_ROOT = /usr/local/Cellar/boost/1.64.0_1
    exists($$BOOST_ROOT) {
        INCLUDEPATH += $$BOOST_ROOT/include
        LIBS        += -L$$BOOST_ROOT/lib -lboost_system
    }
}

SOURCES += \
    qpscaleengine.cpp \
    qpplotitem.cpp \
    qptightscaleengine.cpp \
    qpcurve.cpp \
    qpscrollingcurve.cpp \
    qpfixedscaleengine.cpp \
    quickplotqmlplugin.cpp

HEADERS += \
    qpscaleengine.h \
    qpplotitem.h \
    qptightscaleengine.h \
    qpcurve.h \
    qpscrollingcurve.h \
    qpfixedscaleengine.h \
    quickplotqmlplugin.h

OTHER_FILES += \
    main.qml \
    imports/QuickPlot/Axes.qml \
    imports/QuickPlot/AxisLabels.qml \
    imports/QuickPlot/PlotArea.qml \
    imports/QuickPlot/Tick.qml \
    imports/QuickPlot/qmldir

DESTDIR = ./QuickPlot
QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$PWD/imports/QuickPlot $${DESTDIR}/../
target.path = $$[QT_INSTALL_QML]/QuickPlot
qmldir.path = $$[QT_INSTALL_QML]
qmldir.files = $$PWD/imports/QuickPlot

INSTALLS += target qmldir

