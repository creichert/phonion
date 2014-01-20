
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
                                   messageapploader.source = "qrc:/qml/Chat.qml"
                                 }

                      Rectangle {
                          width: 12; height: 12
                          //border: 6
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
