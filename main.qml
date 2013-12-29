
import QtQuick 2.0

Rectangle  {
    width: 300; height: 400
    color: "white"

    ListModel  {
        id: model
        ListElement { name: "Message"; icon: "" }
        ListElement { name: "Call"; icon: "" }
        ListElement { name: "Browse"; icon: "" }
    }

    Component  {

        id: delegate
        Item  {

            width: 100; height: 100
            Image  {
                id: appIcon
                y: 20; anchors.horizontalCenter: parent.horizontalCenter
                source: icon
            }

            Text  {
                anchors { top: appIcon.bottom;
                          horizontalCenter: parent.horizontalCenter
                        }
                text: name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: { grid.currentIndex = index
                             AppLauncher.launch(index)
                           }
            }
        }
    }

    Component {
        id: highlight
        Rectangle {
            width: grid.cellWidth; height: grid.cellHeight
            color: "lightsteelblue"; radius: 5
            x: grid.currentItem.x
            y: grid.currentItem.y
            Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
            Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
        }
    }

    GridView  {
        id: grid
        anchors.fill: parent
        cellWidth: 100; cellHeight: 100
        highlight: highlight
        focus: true
        model: model
        delegate: delegate
    }
}

