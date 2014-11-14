#include <QtQml/qqml.h>
#include "quickplotqmlplugin.h"

#include "qpplotitem.h"
#include "vumeter.h"
#include "qpscaleengine.h"
#include "qptightscaleengine.h"

void QuickPlotQmlPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("QuickPlot"));
    qmlRegisterType<QPPlotItem>("QuickPlot", 1, 0, "PlotItem");
    qmlRegisterType<VUMeter>("QuickPlot", 1, 0, "VUMeter");
    qmlRegisterType<QPScaleEngine>("QuickPlot", 1, 0, "ScaleEngine");
    qmlRegisterType<QPTightScaleEngine>("QuickPlot", 1, 0, "TightScaleEngine");
}
