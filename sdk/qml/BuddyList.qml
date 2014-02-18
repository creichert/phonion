
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
                      fontpixelsize: 20
                      anchors.left: parent.left
                      anchors.right: parent.right
                      Text {
                          id: dname
                          font.pixelSize: 20
                          text: "<b>" + displayName + "</b>"
                      }
                      Text {
                          anchors.left: dname.right
                          font.pixelSize: 20
                          text: " (" + name + ")"
                      }
                      onClicked: buddyClicked(name)

                      Rectangle {
                          width: 20; height: 20
                          radius: 10
                          anchors.right: parent.right
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
                      }
                  }
    }
}
