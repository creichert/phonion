
import QtQuick 2.0

Rectangle {

    anchors.fill: parent

    ListView {
        id: buddylist
        anchors.fill: parent
        model: buddylistmodel
        delegate: Text {
                      height: 15
                      anchors.left: parent.left
                      anchors.right: parent.right
                      text: name
                      MouseArea {
                          anchors.fill: parent
                          onClicked: { console.log(name)
                                       messagemodel.setCurrentBuddy(name)
                                       messageapploader.source = "qrc:/qml/chat.qml"
                                     }
                      }
                  }
    }
}
