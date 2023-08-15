import "../logic/delegates"
import "../ui"
import speechwriter 1.0
import QtQuick

DocumentForm {
    id: root

    property int selectedIndex: -1

    signal changeIndent
    signal moveTriggered

    SentencesModel {
        id: sentencesModel
    }

    sentencesList.model: sentencesModel
    sentencesList.delegate: SentenceDelegate {
        id: delegate

        width: sentencesList.width

        textEdit.onFocusChanged: {
            selectedIndex = textEdit.focus ? index : -1
        }

        Connections {
            target: root

            function onChangeIndent() {
                if (selectedIndex === index) {
                    delegate.changeIndent()
                }
            }

            function onSelectedIndexChanged() {
                if (selectedIndex === index) {
                    delegate.textEdit.focus = true
                }
            }

            function onMoveTriggered() {
                if (selectedIndex === index) {
                    delegate.moveTriggered()
                }
            }
        }
    }

    addButton.mouseArea.onClicked: {
        sentencesModel.addSentence()
    }

    removeButton.enabled: (selectedIndex >= 0)
    removeButton.mouseArea.onClicked: {
        sentencesModel.removeSentence(selectedIndex)
        selectedIndex = -1
    }

    moveUpButton.enabled: (selectedIndex > 0)
    moveUpButton.mouseArea.onClicked: {
        moveTriggered()
        if (sentencesModel.swapSentence(selectedIndex - 1, selectedIndex)) {
            selectedIndex -= 1
        }
    }

    moveDownButton.enabled: (selectedIndex >= 0) && (selectedIndex < (sentencesList.count - 1))
    moveDownButton.mouseArea.onClicked: {
        moveTriggered()
        if (sentencesModel.swapSentence(selectedIndex + 1, selectedIndex)) {
            selectedIndex += 1
        }
    }

    indentButton.enabled: (selectedIndex >= 0)
    indentButton.mouseArea.onClicked: {
        changeIndent()
    }

    prevDuplicateButton.enabled: (selectedIndex >= 0) && sentencesModel.duplicated(selectedIndex)
    prevDuplicateButton.mouseArea.onClicked: {
        selectedIndex = sentencesModel.prevDuplicatedIndex(selectedIndex)
    }

    nextDuplicateButton.enabled: (selectedIndex >= 0) && sentencesModel.duplicated(selectedIndex)
    nextDuplicateButton.mouseArea.onClicked: {
        selectedIndex = sentencesModel.nextDuplicatedIndex(selectedIndex)
    }

    importButton.mouseArea.onClicked: {
        app.document.loadSentences(importPath)
    }

    exportButton.mouseArea.onClicked: {
        app.document.saveSentences(exportPath)
    }
}
