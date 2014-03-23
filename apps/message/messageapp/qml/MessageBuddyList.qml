
import QtQuick 2.0
import "." // QTBUG-34418

BuddyList {
    anchors.fill: parent

    onBuddyClicked: { console.log("Chatting with " + buddy)
                      messagemodel.setCurrentBuddy(buddy)
                      messageapploader.source = "qrc:/qml/Chat.qml"
                    }

    Button {
        id: addbuddybutton
        fontfamily: Style.fontawesome.family
        fontpixelsize: 16
        text: Style.fontawesome.icon.plus
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
        renderType: Text.NativeRendering
    }
}
