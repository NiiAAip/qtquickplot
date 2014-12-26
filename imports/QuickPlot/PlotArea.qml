import QtQuick 2.0
import QuickPlot 1.0

Item {
    width: 400
    height: 300

    property alias hasXTicks: xlabels.visible
    property alias hasYTicks: ylabels.visible
    property alias axes: axes

    property var xScaleEngine: TightScaleEngine {
        axis: Qt.XAxis
    }

    property var yScaleEngine : TightScaleEngine {
        axis: Qt.YAxis
    }

    onXScaleEngineChanged: {
        xScaleEngine.axis = Qt.XAxis;
        this._updateDependencies();
    }
    onYScaleEngineChanged: {
        yScaleEngine.axis = Qt.YAxis;
        this._updateDependencies();
    }

    AxisLabels {
        id: ylabels
        scaleEngine: yScaleEngine

        anchors {
            top: parent.top
            left: parent.left
            bottom: xlabels.top
        }
    }

    AxisLabels {
        id: xlabels
        scaleEngine: xScaleEngine

        anchors {
            left: ylabels.right
            right: parent.right
            bottom: parent.bottom
        }
    }

    Axes {
        id: axes
        xScaleEngine: parent.xScaleEngine
        yScaleEngine: parent.yScaleEngine

        anchors {
            left: ylabels.right;
            right: parent.right;
            top: parent.top;
            bottom: xlabels.top;
        }
    }

    property list<PlotItem> items

    Component.onCompleted: onItemsChanged.connect(this._updateDependencies);

    function _updateDependencies() {
        for (var i = 0; i < items.length; ++i) {
            items[i].parent = this;
            items[i].xScaleEngine = xScaleEngine;
            items[i].yScaleEngine = yScaleEngine;
            items[i].anchors.left = ylabels.right;
            items[i].anchors.right = right;
            items[i].anchors.top = top;
            items[i].anchors.bottom = xlabels.top;
        }
        xScaleEngine.plotItems = items;
        yScaleEngine.plotItems = items;
    }
}
