import "../../ui/delegates"
import QtQuick

SentenceDelegateForm {
    signal changeIndent
    signal moveTriggered

    Item {
        id: privateProps

        property bool showHint: (model.text.length === 0) && !textEdit.focus
    }

    textEdit.text: privateProps.showHint ? qsTr("click to edit") : model.text
    textEdit.opacity: privateProps.showHint ? 0.15 : 1

    indentActive: model.firstInParagraph
    duplicated: model.duplicated && model.text.length

    onChangeIndent: {
        model.firstInParagraph = !model.firstInParagraph
    }

    onMoveTriggered: {
        model.text = textEdit.text
    }

    Connections {
        target: textEdit

        function onEditingFinished() {
            model.text = textEdit.text
        }
    }

    Connections {
        target: textEdit.Keys

        function onReturnPressed() {
            textEdit.focus = false
        }
    }
}
