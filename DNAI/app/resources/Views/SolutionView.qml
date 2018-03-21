import QtQuick 2.0

import DNAI.Views 1.0
import "../Components"
import "../JavaScript/CreateComponent.js" as Factory

ViewZone {
    id: _parent
    property Modal openModal: null
    property Modal newModal: null
    visualsize: 0

    anchors.fill: parent
    TabView {
        id: tabV
        anchors.fill: parent
        Component.onCompleted: {
            addView("resources/Views/DefaultView.qml",
                    {
                        "openModal" : _parent.openModal,
                        "newModal" : _parent.newModal
                    },
                    "Welcome")
//            selectStart()
        }
    }
    Component.onCompleted: {
        split(1, parent.parent.width, parent.parent.height, 0.2)
        Factory.createObjects("resources/Views/SolutionExplorer.qml", {}, tabV.parent.parent.prev.content)
        var obj = Factory.getObject()
//        obj.title = "Solution Explorer";
        obj.anchors.fill = obj.parent
    }
}
