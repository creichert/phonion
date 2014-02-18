
import QtQuick 2.0

Rectangle {

    signal buddyClicked(string buddy)

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
                      onClicked: buddyClicked(name)

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
}
