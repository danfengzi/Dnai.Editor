import QtQuick 2.0


Item {
    id: splitter
    property bool isVertical: true
    property real xmin: 0
    property real xmax: 4000
    property real ymin: 0
    property real ymax: 4000
    property real handlesize: 2

    function updateMinX(val)
    {
        xmin = val
    }

    function updateMaxX(val)
    {
        xmax = val
    }

    function updateMinY(val)
    {
        ymin = val
    }

    function updateMaxY(val)
    {
        ymax = val
    }

    z: 10
    Rectangle {
        anchors.fill: parent
        visible: mouseArea.containsMouse || mouseArea.pressed
        color: "#80000000"
    }

    Rectangle {
        anchors.centerIn: parent
        height: splitter.isVertical ? parent.height : handlesize
        width: !splitter.isVertical ? parent.width : handlesize
        color: "#000000"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: splitter
        drag.axis: splitter.isVertical ? Drag.XAxis : Drag.YAxis
        drag.minimumX: xmin
        drag.maximumX: xmax - splitter.width
        drag.minimumY: ymin
        drag.maximumY: ymax - splitter.height
        hoverEnabled: true
        cursorShape: splitter.isVertical ? Qt.SplitHCursor : Qt.SplitVCursor
    }
}
