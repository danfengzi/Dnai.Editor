import QtQuick 2.9
import QtQuick.Controls 2.2

import DNAI 1.0
import DNAI.Views 1.0

import "../Style"

TabButton {
    id: _control
    property bool closeButton: true
    property alias label: _text
    property alias back: _background
    property StackView stack: undefined
    property Item refContent: undefined
    property TabBar refTabBar: undefined
    implicitHeight: 20
    width: implicitWidth + 40
    contentItem: MLabel {
        id: _text
        text: qsTr(_control.text)
        anchors.fill: parent

        Button {
            id: _button
            visible: closeButton
            anchors.right: parent.right
            contentItem: Text {
                text: qsTr("\uf057")
                color: _button.hovered ? "#C62828" : DulySettings.style.background.darkColor
                font.family: "Font Awesome 5 Free Solid"
            }
            background: Item {}
            onClicked: {
                if (refContent !== undefined && stack !== undefined && refTabBar !== undefined)
                {
                    stack.pop(refContent, StackView.Immediate)
                    if (refTabBar.currentIndex === 0)
                        refTabBar.incrementCurrentIndex()
                    else
                        refTabBar.decrementCurrentIndex()
                    refTabBar.removeItem(_control)
                }
            }
        }
    }
    background: Rectangle {
        id: _background
        implicitHeight: 40
        height: implicitHeight
        antialiasing: true
        color: _control.checked ? DulySettings.style.background.color : "transparent"
        border.color: DulySettings.style.border.color
        border.width: 1
    }
}

