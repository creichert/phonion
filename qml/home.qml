import QtQuick 2.0

Rectangle  {

    ListModel  {
        id: model
        ListElement { name: "Message"; icon: "qrc:/message.png" }
        ListElement { name: "Call"; icon: "qrc:/phone.png" }
        ListElement { name: "Browse"; icon: "" }
        ListElement { name: "Settings"; icon: "" }
    }

    Component  {

        id: delegate
        Item  {

            width: 100; height: 100
            Image  {
                id: appIcon
                source: icon

                width: 60; height: 60
                y: 20; anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
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
                             loader.source = AppLauncher.launch(index)
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
        anchors.horizontalCenter: parent.horizontalCenter
        cellWidth: 100; cellHeight: 100
        highlight: highlight
        focus: true
        model: model
        delegate: delegate
    }

    Text {
        id: onion
        font.pointSize: 12
        text: AppLauncher.onion()
        anchors.bottom: grid.bottom
        anchors.horizontalCenter: grid.horizontalCenter
    }
}
