#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "qpscaleengine.h"
#include "qpnicescaleengine.h"
#include "vumeter.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QPPlotItem>("QuickPlot", 0, 1, "PlotItem");
    qmlRegisterType<VUMeter>("QuickPlot", 0, 1, "VUMeter");
    qmlRegisterType<QPScaleEngine>("QuickPlot", 0, 1, "ScaleEngine");
    qmlRegisterType<QPNiceScaleEngine>("QuickPlot", 0, 1, "NiceScaleEngine");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
