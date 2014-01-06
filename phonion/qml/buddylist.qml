
import QtQuick 2.0

Rectangle {

    anchors.fill: parent

    ListView {
        id: buddylist
        anchors.fill: parent
        model: buddylistmodel
        delegate: Button {
                      height: 15
                      anchors.left: parent.left
                      anchors.right: parent.right
                      text: name
                      onClicked: { console.log(name)
                                   messagemodel.setCurrentBuddy(name)
                                   messageapploader.source = "qrc:/qml/chat.qml"
                                 }
                  }
    }

    Button {
        id: addbuddybutton
        text: "+"
        anchors.bottom: parent.bottom
        onClicked: { MessageApp.addBuddy(newbuddy.text) }
    }

    TextInput {
        id: newbuddy
        anchors.left: addbuddybutton.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
