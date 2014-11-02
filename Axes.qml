import QtQuick 2.0

Item {
    property var xScaleEngine
    property var yScaleEngine
    property color color: "black"
    property color zeroLineColor: Qt.rgba(0.5, 0.5, 0.5, 0.5)

    property alias hasXZeroLine: xzeroline.visible
    property alias hasYZeroLine: yzeroline.visible

    Rectangle {
        width: 1
        color: parent.color
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            leftMargin: -1
        }
    }

    Rectangle {
        height: 1
        color: parent.color
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            bottomMargin: -1
        }
    }

    Rectangle {
        id: xzeroline
        width: 1
        height: parent.height
        color: parent.zeroLineColor

        x: xScaleEngine.map(0, Qt.rect(0, 0, parent.width, parent.height), xScaleEngine.min, xScaleEngine.max)
        visible: x > 0 && x < parent.width
    }

    Rectangle {
        id: yzeroline
        height: 1
        width: parent.width
        color: parent.zeroLineColor

        y: yScaleEngine.map(0, Qt.rect(0, 0, parent.width, parent.height), yScaleEngine.min, yScaleEngine.max)
        visible: y > 0 && y < parent.height
    }
}
