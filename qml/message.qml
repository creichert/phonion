
import QtQuick 2.0

Rectangle  {

   anchors.fill: parent

   Text {
        id: messages
        anchors.top: parent.top
        anchors.bottom: input.top
        anchors.horizontalCenter: parent.horizontalCenter
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
        console.log("me: " + input.text); 

        var text = messages.text + "\nme: " + input.text
        messages.text = text

        input.text = ""
    }

    function onMessageRecieve() {
    }
}
