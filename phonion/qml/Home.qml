import QtQuick 2.0

Rectangle  {

    Component  {

        id: delegate
        Rectangle  {

            width: grid.cellWidth; height: grid.cellHeight
            Rectangle {
                id: iconrect

                width: parent.width / 1.5; height: parent.height / 1.5

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                border.color: "black"
                radius: 6

                Image  {
                    id: appIcon
                    source: icon

                    width: parent.width - 5; height: parent.height - 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { grid.currentIndex = index
                                 loader.source = app.launch(index)
                               }
                }
            }

            Text  {
                anchors { top: iconrect.bottom;
                          horizontalCenter: parent.horizontalCenter
                        }
                text: name
            }
        }
    }

    GridView  {
        id: grid
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        cellWidth: width / 2; cellHeight: height / 3.5
        //focus: true
        model: appmodel
        delegate: delegate
    }

    Text {
        id: onion
        font.pointSize: 12
        text: app.onion()
        anchors.bottom: grid.bottom
        anchors.horizontalCenter: grid.horizontalCenter
    }
}
