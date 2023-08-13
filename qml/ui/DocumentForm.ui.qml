import "../logic/components"
import QtQuick

Item {
    property alias sentencesList: sentencesList
    property alias addButton: addButton
    property alias removeButton: removeButton
    property alias moveUpButton: moveUpButton
    property alias moveDownButton: moveDownButton
    property alias indentButton: indentButton
    property alias importButton: importButton
    property alias importPath: importPath.text
    property alias exportButton: exportButton
    property alias exportPath: exportPath.text
    property alias prevDuplicateButton: prevDuplicateButton
    property alias nextDuplicateButton: nextDuplicateButton

    ListView {
        id: sentencesList

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: editBar.top
    }

    Item {
        id: editBar

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        height: 130

        Rectangle {
            id: editBarSeparator

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            height: 3

            color: "grey"
        }

        Row {
            id: editSection

            anchors.top: editBarSeparator.bottom
            anchors.topMargin: 8

            spacing: 10

            SimpleButton {
                id: addButton

                text: qsTr("Add Sentence")
            }

            SimpleButton {
                id: removeButton

                text: qsTr("Remove Sentence")
            }

            SimpleButton {
                id: moveUpButton

                text: qsTr("Move Up")
            }

            SimpleButton {
                id: moveDownButton

                text: qsTr("Move Down")
            }

            SimpleButton {
                id: indentButton

                text: qsTr("Set Indent")
            }

            SimpleButton {
                id: prevDuplicateButton

                text: qsTr("Prev Duplicate")
            }

            SimpleButton {
                id: nextDuplicateButton

                text: qsTr("Next Duplicate")
            }
        }

        Row {
            id: importSection

            anchors.top: editSection.bottom
            anchors.topMargin: 8

            spacing: 10

            SimpleButton {
                id: importButton

                text: qsTr("Import")
            }

            TextEdit {
                id: importPath

                width: 300

                text:  qsTr("import path")

                font.pixelSize: 15
                font.italic: true
            }
        }

        Row {
            id: exportSection

            anchors.top: importSection.bottom
            anchors.topMargin: 8

            spacing: 10

            SimpleButton {
                id: exportButton

                text: qsTr("Export")
            }

            TextEdit {
                id: exportPath

                width: 300

                text:  qsTr("export path")

                font.pixelSize: 15
                font.italic: true
            }
        }
    }
}
