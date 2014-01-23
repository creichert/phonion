
import QtQuick 2.0

Rectangle {

    anchors.fill: parent

    ListView {
        id: buddylist
        clip: true
        anchors.fill: parent
        model: buddylistmodel
        delegate: Button {
                      fontpixelsize: 14
                      anchors.left: parent.left
                      anchors.right: parent.right
                      text: name + " (" + displayName + ")"
                      onClicked: { console.log("Chatting with " + name)
                                   messagemodel.setCurrentBuddy(name)
                                   messageapploader.source = "qrc:/qml/Message.qml"
                                 }

                      Rectangle {
                          width: 14; height: 14
                          radius: 7
                          anchors.rightMargin: 2
                          color: { if (status == 1)
                                       return "steelblue"
                                   else if (status == 2)
                                       return "green"
                                   else if (status == 3)
                                       return "yellow"
                                   else
                                       return "red"
                                 }

                          anchors.right: parent.right
                      }
                  }
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
