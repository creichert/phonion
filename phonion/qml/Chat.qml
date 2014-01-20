
import QtQuick 2.0

Rectangle  {

    anchors.fill: parent
    Text {
        id: to
        text: messagemodel.currentBuddy()
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
    }

    ListView {
        id: messages

        clip: true

        anchors.top: to.bottom
        anchors.bottom: input.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: messagemodel
        delegate: Text { text: msg
                         horizontalAlignment: { if (fromme)
                                                    Text.AlignRight
                                                else
                                                    Text.AlignLeft
                                              }
                         width: parent.width
                         wrapMode: Text.WordWrap
                       }

        onCountChanged: { positionViewAtIndex(count-1, ListView.Contain) }
    }

    TextInput {
        id: input
        focus: true
        anchors.bottom: parent.bottom
        anchors.right: send.left
        anchors.left: parent.left

        Keys.onReturnPressed: { send.clicked() }
    }

    Button {
        id: send
        text: "send"

        anchors.right: parent.right
        anchors.top: input.top
        anchors.bottom: input.bottom
    }

    Component.onCompleted: {
        send.clicked.connect(onMessageSend)
    }

    function onMessageSend() {
        MessageApp.sendChatMessage(input.text)
        input.text = ""
    }
}
