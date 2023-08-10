import QtQuick

Item {
    id: root

    property alias text: text.text
    property alias mouseArea: mouseArea

    width: 150
    height: 30

    opacity: enabled ? 1 : 0.2

    Rectangle {
        id: background

        anchors.fill: parent

        radius: 10
        color: "grey"
        opacity: mouseArea.pressed ? 0.2 : 0.4
    }

    Text {
        id: text

        anchors.centerIn: parent

        font {
            family: "Arial"
            pixelSize: 15
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
    }
}
