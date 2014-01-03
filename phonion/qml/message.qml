
import QtQuick 2.0

Rectangle  {

    anchors.fill: parent

    TextInput {
        id: to
        text: messagemodel.currentBuddy()
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView {
        id: messages

        anchors.top: to.bottom
        anchors.bottom: input.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: messagemodel
        delegate: Text { text: msg }
    }

    TextInput {
        id: input
        focus: true
        anchors.bottom: parent.bottom
        anchors.right: send.right
        anchors.horizontalCenter: parent.horizontalCenter

        Keys.onReturnPressed: { send.clicked() }
    }

    Button {
        id: send
        anchors.right: parent.right
        anchors.top: messages.bottom
        anchors.bottom: parent.bottom
    }

    Component.onCompleted: {
        send.clicked.connect(onMessageSend)
    }

    function onMessageSend() {
        MessageApp.sendChatMessage(input.text)
        input.text = ""
    }
}
