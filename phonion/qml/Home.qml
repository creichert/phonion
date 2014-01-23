import QtQuick 2.0

Rectangle  {

    ListModel  {
        id: model
        ListElement { name: "Phone"; icon: "qrc:/phone.png" }
        ListElement { name: "Message"; icon: "qrc:/message.png" }
        ListElement { name: "Browser"; icon: "" }
        ListElement { name: "Email"; icon: "" }
        ListElement { name: "Wallet"; icon: "" }
        ListElement { name: "Settings"; icon: "" }
    }

    Component  {

        id: delegate
        Rectangle  {

            width: 100; height: 100
            border.color: "black"
            radius: 6

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
                             loader.source = app.launch(index)
                           }
            }
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
        text: app.prettyOnion()
        anchors.bottom: grid.bottom
        anchors.horizontalCenter: grid.horizontalCenter
    }
}
