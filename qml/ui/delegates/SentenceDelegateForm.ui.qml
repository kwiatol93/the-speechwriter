import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    property bool indentActive: false
    property bool duplicated: false
    property alias textEdit: textEdit

    height: 36

    Rectangle {
        anchors.fill: parent

        border.width: textEdit.focus ? 1 : 0
        border.color: textEdit.focus ? "grey" : "white"

        Item {
            id: indent

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 1

            width: indentActive ? 40 : 0
            height: root.height - 2
        }

        TextArea {
            id: textEdit

            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: indent.right
            anchors.right: parent.right

            height: root.height - 2

            color: duplicated ? "red" : "black"

            font {
                family: "Arial"
                pixelSize: 20
                italic: true
            }
        }
    }
}
