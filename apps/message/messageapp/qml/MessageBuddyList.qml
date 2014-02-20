
import QtQuick 2.0

BuddyList {
    anchors.fill: parent

    onBuddyClicked: { console.log("Chatting with " + buddy)
                      messagemodel.setCurrentBuddy(buddy)
                      messageapploader.source = "qrc:/qml/Chat.qml"
                    }

    Button {
        id: addbuddybutton
        text: "+"
        anchors.bottom: parent.bottom
        onClicked: { MessageApp.addBuddy(newbuddy.text)
                     newbuddy.text = ""
                   }
    }

    TextInput {
        id: newbuddy
        anchors.left: addbuddybutton.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
